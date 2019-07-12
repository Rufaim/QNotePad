#-------------------------------------------------
#
# Project created by QtCreator 2019-07-08T00:01:16
#
# Maintainer: Pavel Rumyantsev
#
#
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qnotepad
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        about.cpp \
        main.cpp \
        q_note_pad_editor.cpp \
        settings.cpp \
        utils.cpp

HEADERS += \
        about.h \
        q_note_pad_editor.h \
        settings.h \
        settings_context.h \
        utils.h

FORMS += \
        about.ui \
        q_note_pad_editor.ui \
        settings.ui

copydata.commands = $(COPY_DIR) $$PWD/icons $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
# we set a custom build target, in which we first perform file compiling and then the rest, which follows the QMake script
QMAKE_EXTRA_TARGETS += first copydata

RESOURCES += \
    resourses.qrc

