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
        data/game_data.cpp \
        data/pawn_data.cpp \
        data/pawn_type.cpp \
        main.cpp \
        editorwindow.cpp \
        dialog_windows/dialog_enter_level.cpp \
        map/item_delegate_map.cpp \
        map/widget_map.cpp \
        map/table_model_map.cpp \
        pawn_info/item_delegate_pawn.cpp \
        pawn_info/table_model_pawn.cpp \
        pawn_info/widget_objects.cpp \
        pawn_type/widget_object_types.cpp \
        pawn_type/list_model_object_types.cpp

HEADERS += \
        data/game_data.h \
        data/pawn_data.h \
        data/pawn_type.h \
        editorwindow.h \
        dialog_windows/dialog_enter_level.h \
        map/item_delegate_map.h \
        map/widget_map.h \
        map/table_model_map.h \
        pawn_info/item_delegate_pawn.h \
        pawn_info/table_model_pawn.h \
        pawn_info/widget_objects.h \
        pawn_type/widget_object_types.h \
        pawn_type/list_model_object_types.h

FORMS += \
        dialog_windows/dialog_enter_level.ui \
        map/widget_map.ui \
        pawn_info/widget_objects.ui \
        pawn_type/widget_object_types.ui \
        editorwindow.ui

INCLUDEPATH += $$PWD/include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
