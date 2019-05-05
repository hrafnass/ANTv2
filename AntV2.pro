#-------------------------------------------------
#
# Project created by QtCreator 2019-05-05T19:47:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AntV2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    src/background/calculation.cpp \
    src/background/run.cpp \
    src/background/saving.cpp \
    src/background/trial.cpp \
    src/gui/dialogs/game/breakdialog.cpp \
    src/gui/dialogs/game/savedialog.cpp \
    src/gui/dialogs/main/aboutgamedialog.cpp \
    src/gui/dialogs/main/helpdialog.cpp \
    src/gui/dialogs/main/reminder.cpp \
    src/gui/gamewindow.cpp \
    src/gui/mainwindow.cpp \
    src/main.cpp

HEADERS += \
    src/gui/gamewindow.h \
    src/background/calculation.h \
    src/background/run.h \
    src/background/saving.h \
    src/background/trial.h \
    src/gui/dialogs/game/breakdialog.h \
    src/gui/dialogs/game/savedialog.h \
    src/gui/dialogs/main/aboutgamedialog.h \
    src/gui/dialogs/main/helpdialog.h \
    src/gui/dialogs/main/reminder.h \
    src/gui/mainwindow.h

FORMS += \
    src/gui/dialogs/game/breakdialog.ui \
    src/gui/dialogs/game/savedialog.ui \
    src/gui/gamewindow.ui \
    src/gui/mainwindow.ui \
    src/gui/dialogs/main/helpdialog.ui \
    src/gui/dialogs/main/aboutgamedialog.ui \
    src/gui/dialogs/main/reminder.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/gui/ressources.qrc \
    src/gui/ressources.qrc

DISTFILES += \
    src/gui/ressources/images/arrow_left.svg \
    src/gui/ressources/images/arrow_right.svg \
    src/gui/ressources/images/false.svg \
    src/gui/ressources/images/free_space.svg \
    src/gui/ressources/images/plus.svg \
    src/gui/ressources/images/right.svg \
    src/gui/ressources/images/star.svg \
    src/gui/ressources/images/arrow_left.svg \
    src/gui/ressources/images/arrow_right.svg \
    src/gui/ressources/images/false.svg \
    src/gui/ressources/images/free_space.svg \
    src/gui/ressources/images/plus.svg \
    src/gui/ressources/images/right.svg \
    src/gui/ressources/images/star.svg
