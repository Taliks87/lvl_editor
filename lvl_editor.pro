#-------------------------------------------------
#
# Project created by QtCreator 2019-08-10T11:42:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lvl_editor
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
        gui/dialog_enter_level.cpp \
        gui/editorwindow.cpp \
        gui/objecttype.cpp \
        main.cpp \
        core/editor.cpp \
        core/game_object.cpp \
        core/game_object_description.cpp \
        core/level_map.cpp


HEADERS += \
        gui/dialog_enter_level.h \
        gui/editorwindow.h \
        gui/objecttype.h \
        core/config.h \
        core/editor.h \
        core/game_object.h \
        core/game_object_description.h \
        core/level_map.h


FORMS += \
        gui/dialog_enter_level.ui \
        gui/editorwindow.ui \
        gui/objecttype.ui

INCLUDEPATH += $$PWD/include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/game_icon/gameicon.qrc \
    res/icon/icon.qrc
