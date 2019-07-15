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
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DIR_SOURSES = "$$PWD/sourses/src"
DIR_UI = "$$PWD/sourses/ui"
DIR_HEADERS = "$$PWD/sourses/include"
DIR_RESOURSE = "$$PWD/resourses"

SOURCES += \
        $$DIR_SOURSES/about.cpp \
        $$DIR_SOURSES/main.cpp \
        $$DIR_SOURSES/q_note_pad_editor.cpp \
        $$DIR_SOURSES/settings.cpp \
        $$DIR_SOURSES/utils.cpp

HEADERS += \
        $$DIR_HEADERS/about.h \
        $$DIR_HEADERS/q_note_pad_editor.h \
        $$DIR_HEADERS/settings.h \
        $$DIR_HEADERS/settings_context.h \
        $$DIR_HEADERS/utils.h

FORMS += \
        $$DIR_UI/about.ui \
        $$DIR_UI/q_note_pad_editor.ui \
        $$DIR_UI/settings.ui

RESOURCES += \
    $$DIR_RESOURSE/resourses.qrc

copydata.commands = $(COPY_DIR) $$DIR_RESOURSE/icons $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
# we set a custom build target, in which we first perform file compiling and then the rest, which follows the QMake script
QMAKE_EXTRA_TARGETS += first copydata


