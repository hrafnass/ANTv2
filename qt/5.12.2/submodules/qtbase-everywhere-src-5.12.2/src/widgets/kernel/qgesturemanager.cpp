/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWidgets module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "private/qgesturemanager_p.h"
#include "private/qstandardgestures_p.h"
#include "private/qwidget_p.h"
#include "private/qgesture_p.h"
#if QT_CONFIG(graphicsview)
#include "private/qgraphicsitem_p.h"
#include "qgraphicsitem.h"
#endif
#include "private/qevent_p.h"
#include "private/qapplication_p.h"
#include "private/qwidgetwindow_p.h"
#include "qgesture.h"
#include "qevent.h"

#ifdef Q_OS_OSX
#include "qmacgesturerecognizer_p.h"
#endif
#if 0 /* Used to be included in Qt4 for Q_WS_WIN */ && !defined(QT_NO_NATIVE_GESTURES)
#include "qwinnativepangesturerecognizer_win_p.h"
#endif

#include "qdebug.h"
#include <QtCore/QLoggingCategory>

#ifndef QT_NO_GESTURES

QT_BEGIN_NAMESPACE

Q_LOGGING_CATEGORY(lcGestureManager, "qt.widgets.gestures")

#if !defined(Q_OS_OSX)
static inline int panTouchPoints()
{
    // Override by environment variable for testing.
    static const char panTouchPointVariable[] = "QT_PAN_TOUCHPOINTS";
    if (qEnvironmentVariableIsSet(panTouchPointVariable)) {
        bool ok;
        const int result = qEnvironmentVariableIntValue(panTouchPointVariable, &ok);
        if (ok && result >= 1)
            return result;
        qWarning("Ignoring invalid value of %s", panTouchPointVariable);
    }
    // Pan should use 1 finger on a touch screen and 2 fingers on touch pads etc.
    // where 1 finger movements are used for mouse event synthetization. For now,
    // default to 2 until all classes inheriting QScrollArea are fixed to handle it
    // correctly.
    return 2;
}
#endif

QGestureManager::QGestureManager(QObject *parent)
    : QObject(parent), state(NotGesture), m_lastCustomGestureId(Qt::CustomGesture)
{
    qRegisterMetaType<Qt::GestureState>();

#if defined(Q_OS_OSX)
    registerGestureRecognizer(new QMacSwipeGestureRecognizer);
    registerGestureRecognizer(new QMacPinchGestureRecognizer);
    registerGestureRecognizer(new QMacPanGestureRecognizer);
#else
    registerGestureRecognizer(new QPanGestureRecognizer(panTouchPoints()));
    registerGestureRecognizer(new QPinchGestureRecognizer);
    registerGestureRecognizer(new QSwipeGestureRecognizer);
    registerGestureRecognizer(new QTapGestureRecognizer);
#endif
#if 0 // Used to be included in Qt4 for Q_WS_WIN
  #if !defined(QT_NO_NATIVE_GESTURES)
    if (QApplicationPrivate::HasTouchSupport)
        registerGestureRecognizer(new QWinNativePanGestureRecognizer);
  #endif
#else
    registerGestureRecognizer(new QTapAndHoldGestureRecognizer);
#endif
}

QGestureManager::~QGestureManager()
{
    qDeleteAll(m_recognizers);
    foreach (QGestureRecognizer *recognizer, m_obsoleteGestures.keys()) {
        qDeleteAll(m_obsoleteGestures.value(recognizer));
        delete recognizer;
    }
    m_obsoleteGestures.clear();
}

Qt::GestureType QGestureManager::registerGestureRecognizer(QGestureRecognizer *recognizer)
{
    const QScopedPointer<QGesture> dummy(recognizer->create(nullptr));
    if (Q_UNLIKELY(!dummy)) {
        qWarning("QGestureManager::registerGestureRecognizer: "
                 "the recognizer fails to create a gesture object, skipping registration.");
        return Qt::GestureType(0);
    }
    Qt::GestureType type = dummy->gestureType();
    if (type == Qt::CustomGesture) {
        // generate a new custom gesture id
        ++m_lastCustomGestureId;
        type = Qt::GestureType(m_lastCustomGestureId);
    }
    m_recognizers.insertMulti(type, recognizer);
    return type;
}

void QGestureManager::unregisterGestureRecognizer(Qt::GestureType type)
{
    QList<QGestureRecognizer *> list = m_recognizers.values(type);
    while (QGestureRecognizer *recognizer = m_recognizers.take(type)) {
        // ensuring an entry exists causes the recognizer to be deleted on destruction of the manager
        auto &gestures = m_obsoleteGestures[recognizer];
        Q_UNUSED(gestures);
    }
    foreach (QGesture *g, m_gestureToRecognizer.keys()) {
        QGestureRecognizer *recognizer = m_gestureToRecognizer.value(g);
        if (list.contains(recognizer)) {
            m_deletedRecognizers.insert(g, recognizer);
        }
    }

    QMap<ObjectGesture, QList<QGesture *> >::const_iterator iter = m_objectGestures.constBegin();
    while (iter != m_objectGestures.constEnd()) {
        ObjectGesture objectGesture = iter.key();
        if (objectGesture.gesture == type) {
            foreach (QGesture *g, iter.value()) {
                if (QGestureRecognizer *recognizer = m_gestureToRecognizer.value(g)) {
                    m_gestureToRecognizer.remove(g);
                    m_obsoleteGestures[recognizer].insert(g);
                }
            }
        }
        ++iter;
    }
}

void QGestureManager::cleanupCachedGestures(QObject *target, Qt::GestureType type)
{
    QMap<ObjectGesture, QList<QGesture *> >::Iterator iter = m_objectGestures.begin();
    while (iter != m_objectGestures.end()) {
        ObjectGesture objectGesture = iter.key();
        if (objectGesture.gesture == type && target == objectGesture.object) {
            QSet<QGesture *> gestures = iter.value().toSet();
            for (QHash<QGestureRecognizer *, QSet<QGesture *> >::iterator
                 it = m_obsoleteGestures.begin(), e = m_obsoleteGestures.end(); it != e; ++it) {
                it.value() -= gestures;
            }
            foreach (QGesture *g, gestures) {
                m_deletedRecognizers.remove(g);
                m_gestureToRecognizer.remove(g);
                m_maybeGestures.remove(g);
                m_activeGestures.remove(g);
                m_gestureOwners.remove(g);
                m_gestureTargets.remove(g);
                m_gesturesToDelete.insert(g);
            }

            iter = m_objectGestures.erase(iter);
        } else {
            ++iter;
        }
    }
}

// get or create a QGesture object that will represent the state for a given object, used by the recognizer
QGesture *QGestureManager::getState(QObject *object, QGestureRecognizer *recognizer, Qt::GestureType type)
{
    // if the widget is being deleted we should be careful not to
    // create a new state, as it will create QWeakPointer which doesn't work
    // from the destructor.
    if (object->isWidgetType()) {
        if (static_cast<QWidget *>(object)->d_func()->data.in_destructor)
            return 0;
    } else if (QGesture *g = qobject_cast<QGesture *>(object)) {
        return g;
#if QT_CONFIG(graphicsview)
    } else {
        Q_ASSERT(qobject_cast<QGraphicsObject *>(object));
        QGraphicsObject *graphicsObject = static_cast<QGraphicsObject *>(object);
        if (graphicsObject->QGraphicsItem::d_func()->inDestructor)
            return 0;
#endif
    }

    // check if the QGesture for this recognizer has already been created
    const auto states = m_objectGestures.value(QGestureManager::ObjectGesture(object, type));
    for (QGesture *state : states) {
        if (m_gestureToRecognizer.value(state) == recognizer)
            return state;
    }

    Q_ASSERT(recognizer);
    QGesture *state = recognizer->create(object);
    if (!state)
        return 0;
    state->setParent(this);
    if (state->gestureType() == Qt::CustomGesture) {
        // if the recognizer didn't fill in the gesture type, then this
        // is a custom gesture with autogenerated id and we fill it.
        state->d_func()->gestureType = type;
        if (lcGestureManager().isDebugEnabled())
            state->setObjectName(QString::number((int)type));
    }
    m_objectGestures[QGestureManager::ObjectGesture(object, type)].append(state);
    m_gestureToRecognizer[state] = recognizer;
    m_gestureOwners[state] = object;

    return state;
}

static bool logIgnoredEvent(QEvent::Type t)
{
    bool result = false;
    switch (t) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseButtonDblClick:
    case QEvent::MouseMove:
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchCancel:
    case QEvent::TouchEnd:
    case QEvent::TabletEnterProximity:
    case QEvent::TabletLeaveProximity:
    case QEvent::TabletMove:
    case QEvent::TabletPress:
    case QEvent::TabletRelease:
    case QEvent::GraphicsSceneMouseDoubleClick:
    case QEvent::GraphicsSceneMousePress:
    case QEvent::GraphicsSceneMouseRelease:
    case QEvent::GraphicsSceneMouseMove:
        result = true;
        break;
    default:
        break;

    }
    return result;
}

bool QGestureManager::filterEventThroughContexts(const QMultiMap<QObject *,
                                                 Qt::GestureType> &contexts,
                                                 QEvent *event)
{
    QSet<QGesture *> triggeredGestures;
    QSet<QGesture *> finishedGestures;
    QSet<QGesture *> newMaybeGestures;
    QSet<QGesture *> notGestures;

    // TODO: sort contexts by the gesture type and check if one of the contexts
    //       is already active.

    bool consumeEventHint = false;

    // filter the event through recognizers
    typedef QMultiMap<QObject *, Qt::GestureType>::const_iterator ContextIterator;
    ContextIterator contextEnd = contexts.end();
    for (ContextIterator context = contexts.begin(); context != contextEnd; ++context) {
        Qt::GestureType gestureType = context.value();
        const QMap<Qt::GestureType, QGestureRecognizer *> &const_recognizers = m_recognizers;
        QMap<Qt::GestureType, QGestureRecognizer *>::const_iterator
                typeToRecognizerIterator = const_recognizers.lowerBound(gestureType),
                typeToRecognizerEnd = const_recognizers.upperBound(gestureType);
        for (; typeToRecognizerIterator != typeToRecognizerEnd; ++typeToRecognizerIterator) {
            QGestureRecognizer *recognizer = typeToRecognizerIterator.value();
            QObject *target = context.key();
            QGesture *state = getState(target, recognizer, gestureType);
            if (!state)
                continue;
            QGestureRecognizer::Result recognizerResult = recognizer->recognize(state, target, event);
            QGestureRecognizer::Result recognizerState = recognizerResult & QGestureRecognizer::ResultState_Mask;
            QGestureRecognizer::Result resultHint = recognizerResult & QGestureRecognizer::ResultHint_Mask;
            if (recognizerState == QGestureRecognizer::TriggerGesture) {
                qCDebug(lcGestureManager) << "QGestureManager:Recognizer: gesture triggered: " << state << event;
                triggeredGestures << state;
            } else if (recognizerState == QGestureRecognizer::FinishGesture) {
                qCDebug(lcGestureManager) << "QGestureManager:Recognizer: gesture finished: " << state << event;
                finishedGestures << state;
            } else if (recognizerState == QGestureRecognizer::MayBeGesture) {
                qCDebug(lcGestureManager) << "QGestureManager:Recognizer: maybe gesture: " << state << event;
                newMaybeGestures << state;
            } else if (recognizerState == QGestureRecognizer::CancelGesture) {
                qCDebug(lcGestureManager) << "QGestureManager:Recognizer: not gesture: " << state << event;
                notGestures << state;
            } else if (recognizerState == QGestureRecognizer::Ignore) {
                if (logIgnoredEvent(event->type()))
                    qCDebug(lcGestureManager) << "QGestureManager:Recognizer: ignored the event: " << state << event;
            } else {
                if (logIgnoredEvent(event->type())) {
                    qCDebug(lcGestureManager) << "QGestureManager:Recognizer: hm, lets assume the recognizer"
                        << "ignored the event: " << state << event;
                }
            }
            if (resultHint & QGestureRecognizer::ConsumeEventHint) {
                qCDebug(lcGestureManager) << "QGestureManager: we were asked to consume the event: "
                        << state << event;
                consumeEventHint = true;
            }
        }
    }
    if (!triggeredGestures.isEmpty() || !finishedGestures.isEmpty()
        || !newMaybeGestures.isEmpty() || !notGestures.isEmpty()) {
        QSet<QGesture *> startedGestures = triggeredGestures - m_activeGestures;
        triggeredGestures &= m_activeGestures;

        // check if a running gesture switched back to maybe state
        QSet<QGesture *> activeToMaybeGestures = m_activeGestures & newMaybeGestures;

        // check if a maybe gesture switched to canceled - reset it but don't send an event
        QSet<QGesture *> maybeToCanceledGestures = m_maybeGestures & notGestures;

        // check if a running gesture switched back to not gesture state,
        // i.e. were canceled
        QSet<QGesture *> canceledGestures = m_activeGestures & notGestures;

        // new gestures in maybe state
        m_maybeGestures += newMaybeGestures;

        // gestures that were in maybe state
        QSet<QGesture *> notMaybeGestures = (startedGestures | triggeredGestures
                                             | finishedGestures | canceledGestures
                                             | notGestures);
        m_maybeGestures -= notMaybeGestures;

        Q_ASSERT((startedGestures & finishedGestures).isEmpty());
        Q_ASSERT((startedGestures & newMaybeGestures).isEmpty());
        Q_ASSERT((startedGestures & canceledGestures).isEmpty());
        Q_ASSERT((finishedGestures & newMaybeGestures).isEmpty());
        Q_ASSERT((finishedGestures & canceledGestures).isEmpty());
        Q_ASSERT((canceledGestures & newMaybeGestures).isEmpty());

        QSet<QGesture *> notStarted = finishedGestures - m_activeGestures;
        if (!notStarted.isEmpty()) {
            // there are some gestures that claim to be finished, but never started.
            // probably those are "singleshot" gestures so we'll fake the started state.
            foreach (QGesture *gesture, notStarted)
                gesture->d_func()->state = Qt::GestureStarted;
            QSet<QGesture *> undeliveredGestures;
            deliverEvents(notStarted, &undeliveredGestures);
            finishedGestures -= undeliveredGestures;
        }

        m_activeGestures += startedGestures;
        // sanity check: all triggered gestures should already be in active gestures list
        Q_ASSERT((m_activeGestures & triggeredGestures).size() == triggeredGestures.size());
        m_activeGestures -= finishedGestures;
        m_activeGestures -= activeToMaybeGestures;
        m_activeGestures -= canceledGestures;

        // set the proper gesture state on each gesture
        foreach (QGesture *gesture, startedGestures)
            gesture->d_func()->state = Qt::GestureStarted;
        foreach (QGesture *gesture, triggeredGestures)
            gesture->d_func()->state = Qt::GestureUpdated;
        foreach (QGesture *gesture, finishedGestures)
            gesture->d_func()->state = Qt::GestureFinished;
        foreach (QGesture *gesture, canceledGestures)
            gesture->d_func()->state = Qt::GestureCanceled;
        foreach (QGesture *gesture, activeToMaybeGestures)
            gesture->d_func()->state = Qt::GestureFinished;

        if (!m_activeGestures.isEmpty() || !m_maybeGestures.isEmpty() ||
            !startedGestures.isEmpty() || !triggeredGestures.isEmpty() ||
            !finishedGestures.isEmpty() || !canceledGestures.isEmpty()) {
            qCDebug(lcGestureManager) << "QGestureManager::filterEventThroughContexts:"
                    << "\n\tactiveGestures:" << m_activeGestures
                    << "\n\tmaybeGestures:" << m_maybeGestures
                    << "\n\tstarted:" << startedGestures
                    << "\n\ttriggered:" << triggeredGestures
                    << "\n\tfinished:" << finishedGestures
                    << "\n\tcanceled:" << canceledGestures
                    << "\n\tmaybe-canceled:" << maybeToCanceledGestures;
        }

        QSet<QGesture *> undeliveredGestures;
        deliverEvents(startedGestures+triggeredGestures+finishedGestures+canceledGestures,
                      &undeliveredGestures);

        foreach (QGesture *g, startedGestures) {
            if (undeliveredGestures.contains(g))
                continue;
            if (g->gestureCancelPolicy() == QGesture::CancelAllInContext) {
                qCDebug(lcGestureManager) << "lets try to cancel some";
                // find gestures in context in Qt::GestureStarted or Qt::GestureUpdated state and cancel them
                cancelGesturesForChildren(g);
            }
        }

        m_activeGestures -= undeliveredGestures;

        // reset gestures that ended
        QSet<QGesture *> endedGestures =
                finishedGestures + canceledGestures + undeliveredGestures + maybeToCanceledGestures;
        foreach (QGesture *gesture, endedGestures) {
            recycle(gesture);
            m_gestureTargets.remove(gesture);
        }
    }
    //Clean up the Gestures
    qDeleteAll(m_gesturesToDelete);
    m_gesturesToDelete.clear();

    return consumeEventHint;
}

// Cancel all gestures of children of the widget that original is associated with
void QGestureManager::cancelGesturesForChildren(QGesture *original)
{
    Q_ASSERT(original);
    QWidget *originatingWidget = m_gestureTargets.value(original);
    Q_ASSERT(originatingWidget);
    if (!originatingWidget)
        return;

    // iterate over all active gestures and all maybe gestures
    // for each find the owner
    // if the owner is part of our sub-hierarchy, cancel it.

    QSet<QGesture*> cancelledGestures;
    QSet<QGesture*>::Iterator iter = m_activeGestures.begin();
    while (iter != m_activeGestures.end()) {
        QWidget *widget = m_gestureTargets.value(*iter);
        // note that we don't touch the gestures for our originatingWidget
        if (widget != originatingWidget && originatingWidget->isAncestorOf(widget)) {
            qCDebug(lcGestureManager) << "  found a gesture to cancel" << (*iter);
            (*iter)->d_func()->state = Qt::GestureCanceled;
            cancelledGestures << *iter;
            iter = m_activeGestures.erase(iter);
        } else {
            ++iter;
        }
    }

    // TODO handle 'maybe' gestures too

    // sort them per target widget by cherry picking from almostCanceledGestures and delivering
    QSet<QGesture *> almostCanceledGestures = cancelledGestures;
    while (!almostCanceledGestures.isEmpty()) {
        QWidget *target = 0;
        QSet<QGesture*> gestures;
        iter = almostCanceledGestures.begin();
        // sort per target widget
        while (iter != almostCanceledGestures.end()) {
            QWidget *widget = m_gestureTargets.value(*iter);
            if (target == 0)
                target = widget;
            if (target == widget) {
                gestures << *iter;
                iter = almostCanceledGestures.erase(iter);
            } else {
                ++iter;
            }
        }
        Q_ASSERT(target);

        QSet<QGesture*> undeliveredGestures;
        deliverEvents(gestures, &undeliveredGestures);
    }

    for (iter = cancelledGestures.begin(); iter != cancelledGestures.end(); ++iter)
        recycle(*iter);
}

void QGestureManager::cleanupGesturesForRemovedRecognizer(QGesture *gesture)
{
    QGestureRecognizer *recognizer = m_deletedRecognizers.value(gesture);
    if(!recognizer) //The Gesture is removed while in the even loop, so the recognizers for this gestures was removed
        return;
    m_deletedRecognizers.remove(gesture);
    if (m_deletedRecognizers.keys(recognizer).isEmpty()) {
        // no more active gestures, cleanup!
        qDeleteAll(m_obsoleteGestures.value(recognizer));
        m_obsoleteGestures.remove(recognizer);
        delete recognizer;
    }
}

// return true if accepted (consumed)
bool QGestureManager::filterEvent(QWidget *receiver, QEvent *event)
{
    QMap<Qt::GestureType, int> types;
    QMultiMap<QObject *, Qt::GestureType> contexts;
    QWidget *w = receiver;
    typedef QMap<Qt::GestureType, Qt::GestureFlags>::const_iterator ContextIterator;
    if (!w->d_func()->gestureContext.isEmpty()) {
        for(ContextIterator it = w->d_func()->gestureContext.constBegin(),
            e = w->d_func()->gestureContext.constEnd(); it != e; ++it) {
            types.insert(it.key(), 0);
            contexts.insertMulti(w, it.key());
        }
    }
    // find all gesture contexts for the widget tree
    w = w->isWindow() ? 0 : w->parentWidget();
    while (w)
    {
        for (ContextIterator it = w->d_func()->gestureContext.constBegin(),
             e = w->d_func()->gestureContext.constEnd(); it != e; ++it) {
            if (!(it.value() & Qt::DontStartGestureOnChildren)) {
                if (!types.contains(it.key())) {
                    types.insert(it.key(), 0);
                    contexts.insertMulti(w, it.key());
                }
            }
        }
        if (w->isWindow())
            break;
        w = w->parentWidget();
    }
    return contexts.isEmpty() ? false : filterEventThroughContexts(contexts, event);
}

#if QT_CONFIG(graphicsview)
bool QGestureManager::filterEvent(QGraphicsObject *receiver, QEvent *event)
{
    QMap<Qt::GestureType, int> types;
    QMultiMap<QObject *, Qt::GestureType> contexts;
    QGraphicsObject *item = receiver;
    if (!item->QGraphicsItem::d_func()->gestureContext.isEmpty()) {
        typedef QMap<Qt::GestureType, Qt::GestureFlags>::const_iterator ContextIterator;
        for(ContextIterator it = item->QGraphicsItem::d_func()->gestureContext.constBegin(),
            e = item->QGraphicsItem::d_func()->gestureContext.constEnd(); it != e; ++it) {
            types.insert(it.key(), 0);
            contexts.insertMulti(item, it.key());
        }
    }
    // find all gesture contexts for the graphics object tree
    item = item->parentObject();
    while (item)
    {
        typedef QMap<Qt::GestureType, Qt::GestureFlags>::const_iterator ContextIterator;
        for (ContextIterator it = item->QGraphicsItem::d_func()->gestureContext.constBegin(),
             e = item->QGraphicsItem::d_func()->gestureContext.constEnd(); it != e; ++it) {
            if (!(it.value() & Qt::DontStartGestureOnChildren)) {
                if (!types.contains(it.key())) {
                    types.insert(it.key(), 0);
                    contexts.insertMulti(item, it.key());
                }
            }
        }
        item = item->parentObject();
    }
    return contexts.isEmpty() ? false : filterEventThroughContexts(contexts, event);
}
#endif

bool QGestureManager::filterEvent(QObject *receiver, QEvent *event)
{
    // if the receiver is actually a widget, we need to call the correct event
    // filter method.
    QWidgetWindow *widgetWindow = qobject_cast<QWidgetWindow *>(receiver);

    if (widgetWindow && widgetWindow->widget())
        return filterEvent(widgetWindow->widget(), event);

    QGesture *state = qobject_cast<QGesture *>(receiver);
    if (!state || !m_gestureToRecognizer.contains(state))
        return false;
    QMultiMap<QObject *, Qt::GestureType> contexts;
    contexts.insert(state, state->gestureType());
    return filterEventThroughContexts(contexts, event);
}

void QGestureManager::getGestureTargets(const QSet<QGesture*> &gestures,
    QHash<QWidget *, QList<QGesture *> > *conflicts,
    QHash<QWidget *, QList<QGesture *> > *normal)
{
    typedef QHash<Qt::GestureType, QHash<QWidget *, QGesture *> > GestureByTypes;
    GestureByTypes gestureByTypes;

    // sort gestures by types
    foreach (QGesture *gesture, gestures) {
        QWidget *receiver = m_gestureTargets.value(gesture, 0);
        Q_ASSERT(receiver);
        if (receiver)
            gestureByTypes[gesture->gestureType()].insert(receiver, gesture);
    }

    // for each gesture type
    for (GestureByTypes::const_iterator git = gestureByTypes.cbegin(), gend = gestureByTypes.cend(); git != gend; ++git) {
        const QHash<QWidget *, QGesture *> &gestures = git.value();
        for (QHash<QWidget *, QGesture *>::const_iterator wit = gestures.cbegin(), wend = gestures.cend(); wit != wend; ++wit) {
            QWidget *widget = wit.key();
            QWidget *w = widget->parentWidget();
            while (w) {
                QMap<Qt::GestureType, Qt::GestureFlags>::const_iterator it
                        = w->d_func()->gestureContext.constFind(git.key());
                if (it != w->d_func()->gestureContext.constEnd()) {
                    // i.e. 'w' listens to gesture 'type'
                    if (!(it.value() & Qt::DontStartGestureOnChildren) && w != widget) {
                        // conflicting gesture!
                        (*conflicts)[widget].append(wit.value());
                        break;
                    }
                }
                if (w->isWindow()) {
                    w = 0;
                    break;
                }
                w = w->parentWidget();
            }
            if (!w)
                (*normal)[widget].append(wit.value());
        }
    }
}

void QGestureManager::deliverEvents(const QSet<QGesture *> &gestures,
                                    QSet<QGesture *> *undeliveredGestures)
{
    if (gestures.isEmpty())
        return;

    typedef QHash<QWidget *, QList<QGesture *> > GesturesPerWidget;
    GesturesPerWidget conflictedGestures;
    GesturesPerWidget normalStartedGestures;

    QSet<QGesture *> startedGestures;
    // first figure out the initial receivers of gestures
    for (QSet<QGesture *>::const_iterator it = gestures.begin(),
         e = gestures.end(); it != e; ++it) {
        QGesture *gesture = *it;
        QWidget *target = m_gestureTargets.value(gesture, 0);
        if (!target) {
            // the gesture has just started and doesn't have a target yet.
            Q_ASSERT(gesture->state() == Qt::GestureStarted);
            if (gesture->hasHotSpot()) {
                // guess the target widget using the hotspot of the gesture
                QPoint pt = gesture->hotSpot().toPoint();
                if (QWidget *topLevel = QApplication::topLevelAt(pt)) {
                    QWidget *child = topLevel->childAt(topLevel->mapFromGlobal(pt));
                    target = child ? child : topLevel;
                }
            } else {
                // or use the context of the gesture
                QObject *context = m_gestureOwners.value(gesture, 0);
                if (context->isWidgetType())
                    target = static_cast<QWidget *>(context);
            }
            if (target)
                m_gestureTargets.insert(gesture, target);
        }

        Qt::GestureType gestureType = gesture->gestureType();
        Q_ASSERT(gestureType != Qt::CustomGesture);
        Q_UNUSED(gestureType);

        if (Q_UNLIKELY(!target)) {
            qCDebug(lcGestureManager) << "QGestureManager::deliverEvent: could not find the target for gesture"
                    << gesture->gestureType();
            qWarning("QGestureManager::deliverEvent: could not find the target for gesture");
            undeliveredGestures->insert(gesture);
        } else {
            if (gesture->state() == Qt::GestureStarted) {
                startedGestures.insert(gesture);
            } else {
                normalStartedGestures[target].append(gesture);
            }
        }
    }

    getGestureTargets(startedGestures, &conflictedGestures, &normalStartedGestures);
    qCDebug(lcGestureManager) << "QGestureManager::deliverEvents:"
            << "\nstarted: " << startedGestures
            << "\nconflicted: " << conflictedGestures
            << "\nnormal: " << normalStartedGestures
            << "\n";

    // if there are conflicting gestures, send the GestureOverride event
    for (GesturesPerWidget::const_iterator it = conflictedGestures.constBegin(),
        e = conflictedGestures.constEnd(); it != e; ++it) {
        QWidget *receiver = it.key();
        QList<QGesture *> gestures = it.value();
        qCDebug(lcGestureManager) << "QGestureManager::deliverEvents: sending GestureOverride to"
                << receiver
                << "gestures:" << gestures;
        QGestureEvent event(gestures);
        event.t = QEvent::GestureOverride;
        // mark event and individual gestures as ignored
        event.ignore();
        foreach(QGesture *g, gestures)
            event.setAccepted(g, false);

        QApplication::sendEvent(receiver, &event);
        bool eventAccepted = event.isAccepted();
        const auto eventGestures = event.gestures();
        for (QGesture *gesture : eventGestures) {
            if (eventAccepted || event.isAccepted(gesture)) {
                QWidget *w = event.m_targetWidgets.value(gesture->gestureType(), 0);
                Q_ASSERT(w);
                qCDebug(lcGestureManager) << "override event: gesture was accepted:" << gesture << w;
                QList<QGesture *> &gestures = normalStartedGestures[w];
                gestures.append(gesture);
                // override the target
                m_gestureTargets[gesture] = w;
            } else {
                qCDebug(lcGestureManager) << "override event: gesture wasn't accepted. putting back:" << gesture;
                QList<QGesture *> &gestures = normalStartedGestures[receiver];
                gestures.append(gesture);
            }
        }
    }

    // delivering gestures that are not in conflicted state
    for (GesturesPerWidget::const_iterator it = normalStartedGestures.constBegin(),
        e = normalStartedGestures.constEnd(); it != e; ++it) {
        if (!it.value().isEmpty()) {
            qCDebug(lcGestureManager) << "QGestureManager::deliverEvents: sending to" << it.key()
                    << "gestures:" << it.value();
            QGestureEvent event(it.value());
            QApplication::sendEvent(it.key(), &event);
            bool eventAccepted = event.isAccepted();
            const auto eventGestures = event.gestures();
            for (QGesture *gesture : eventGestures) {
                if (gesture->state() == Qt::GestureStarted &&
                    (eventAccepted || event.isAccepted(gesture))) {
                    QWidget *w = event.m_targetWidgets.value(gesture->gestureType(), 0);
                    Q_ASSERT(w);
                    qCDebug(lcGestureManager) << "started gesture was delivered and accepted by" << w;
                    m_gestureTargets[gesture] = w;
                }
            }
        }
    }
}

void QGestureManager::recycle(QGesture *gesture)
{
    QGestureRecognizer *recognizer = m_gestureToRecognizer.value(gesture, 0);
    if (recognizer) {
        gesture->setGestureCancelPolicy(QGesture::CancelNone);
        recognizer->reset(gesture);
        m_activeGestures.remove(gesture);
    } else {
        cleanupGesturesForRemovedRecognizer(gesture);
    }
}

bool QGestureManager::gesturePending(QObject *o)
{
    const QGestureManager *gm = QGestureManager::instance(DontForceCreation);
    return gm && gm->m_gestureOwners.key(o);
}

QT_END_NAMESPACE

#endif // QT_NO_GESTURES

#include "moc_qgesturemanager_p.cpp"
