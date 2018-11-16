#-------------------------------------------------
#
# Project created by QtCreator 2018-11-16T23:26:51
#
#-------------------------------------------------

QT       += testlib

QT       += gui

QT       += widgets

TARGET = tst_gameboardtest
CONFIG   += console
CONFIG   -= app_bundle

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


SOURCES += \
        tst_gameboardtest.cpp \
    ../../../GameLogic/Engine/transport.cpp \
    ../../../GameLogic/Engine/actorfactory.cpp \
    ../../../GameLogic/Engine/actor.cpp \
    ../../../GameLogic/Engine/hex.cpp \
    ../../../GameLogic/Engine/pawn.cpp \
    ../../../UI/gameboard.cpp \
    ../../../GameLogic/Engine/gameexception.cpp \
    ../../../UI/graphicalhex.cpp

HEADERS += \
    ../../../GameLogic/Engine/transport.hh \
    ../../../GameLogic/Engine/actorfactory.hh \
    ../../../GameLogic/Engine/actor.hh \
    ../../../GameLogic/Engine/hex.hh \
    ../../../GameLogic/Engine/igameboard.hh \
    ../../../GameLogic/Engine/pawn.hh \
    ../../../UI/gameboard.hh \
    ../../../GameLogic/Engine/gameexception.hh \
    ../../../UI/graphicalhex.hh

INCLUDEPATH += \
    ../../../UI \
    ../../../GameLogic/Engine
