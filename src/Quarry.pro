#-------------------------------------------------
#
# Project created by QtCreator 2012-05-27T17:47:01
#
#-------------------------------------------------

QT       += core gui\
        webkit

TARGET = Quarry
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ststone.cpp \
    stgold.cpp \
    stmud.cpp \
    stfragile.cpp \
    stmorph.cpp \
    animator.cpp \
    prplayer.cpp \
    prhuman.cpp \
    prcomputer.cpp \
    prmonkey.cpp \
    game.cpp \
    stmulti.cpp \
    paramcurveanimation.cpp

HEADERS  += mainwindow.h \
    ststone.h \
    stgold.h \
    stfragile.h \
    stmorph.h \
    animator.h \
    prplayer.h \
    prhuman.h \
    prcomputer.h \
    stmud.h \
    prmonkey.h \
    game.h \
    stmulti.h \
    paramcurveanimation.h

FORMS    += mainwindow.ui

RESOURCES += \
    qrr.qrc
