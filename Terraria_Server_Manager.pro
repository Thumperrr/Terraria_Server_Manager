#-------------------------------------------------
#
# Project created by QtCreator 2012-10-18T16:01:38
#
#-------------------------------------------------

QT       += core gui

TEMPLATE = app

HEADERS += mainwindow.h \
    Util/Utility.h \
    Util/BinaryReader.h \
    Widgets/ServerTabwidget.h \
    Widgets/Options.h \
    Widgets/ConfigSelector.h \
    Widgets/ConfigManager.h \
    Widgets/ConfigEditor.h

SOURCES += mainwindow.cpp \
        main.cpp \
    Util/Utility.cpp \
    Util/BinaryReader.cpp \
    Widgets/ServerTabWidget.cpp \
    Widgets/Options.cpp \
    Widgets/ConfigSelector.cpp \
    Widgets/ConfigManager.cpp \
    Widgets/ConfigEditor.cpp

FORMS += \
    Ui/ServerTabWidget.ui \
    Ui/Options.ui \
    Ui/mainwindow.ui \
    Ui/ConfigSelector.ui \
    Ui/ConfigManager.ui \
    Ui/ConfigEditor.ui

release:UI_DIR = release/uis
release:MOC_DIR = release/mocs
release:OBJECTS_DIR = release/objs

debug:UI_DIR = debug/uis
debug:MOC_DIR = debug/mocs
debug:OBJECTS_DIR = debug/objs
