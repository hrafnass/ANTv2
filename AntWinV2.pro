#-------------------------------------------------
#
# Project created by QtCreator 2019-05-21T19:17:47
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


CONFIG += c++11
# Added by myself to static link all libs: avoid erros like this libgcc_s_dw2-1.dll doesn't found
# QMAKE_LFLAGS += -static-libgcc -static


RESOURCES = \
    ressources.qrc

FORMS += \
    src/gui/dialogs/game/breakdialog.ui \
    src/gui/dialogs/main/aboutgamedialog.ui \
    src/gui/gamewindow.ui \
    src/gui/mainwindow.ui \
    src/gui/dialogs/game/savedialog.ui \
    src/gui/dialogs/main/reminder.ui \
    src/gui/dialogs/main/excercisedialog.ui

HEADERS += \
    src/background/calculation.h \
    src/background/run.h \
    src/background/saving.h \
    src/background/trial.h \
    src/gui/dialogs/game/breakdialog.h \
    src/gui/dialogs/game/savedialog.h \
    src/gui/dialogs/main/aboutgamedialog.h \
    src/gui/dialogs/main/reminder.h \
    src/gui/gamewindow.h \
    src/gui/mainwindow.h \
    src/gui/dialogs/main/excercisedialog.h

SOURCES += \
    src/background/calculation.cpp \
    src/background/run.cpp \
    src/background/saving.cpp \
    src/background/trial.cpp \
    src/gui/dialogs/game/breakdialog.cpp \
    src/gui/dialogs/game/savedialog.cpp \
    src/gui/dialogs/main/aboutgamedialog.cpp \
    src/gui/dialogs/main/reminder.cpp \
    src/gui/gamewindow.cpp \
    src/gui/mainwindow.cpp \
    src/main.cpp \
    src/gui/dialogs/main/excercisedialog.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
