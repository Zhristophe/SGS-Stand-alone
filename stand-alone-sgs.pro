#-------------------------------------------------
#
# Project created by QtCreator 2018-07-27T22:07:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stand-alone-sgs
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
        main.cpp \
        mainwindow.cpp \
    settings.cpp \
    startscene.cpp \
    roomscene.cpp \
    engine.cpp \
    graphicsscene.cpp \
    carditem.cpp \
    button.cpp \
    operationpanel.cpp \
    card.cpp \
    gameevent.cpp \
    playeritem.cpp \
    player.cpp \
    event.cpp \
    seat.cpp \
    widgets.cpp

HEADERS += \
        mainwindow.h \
    settings.h \
    startscene.h \
    roomscene.h \
    engine.h \
    graphicsscene.h \
    carditem.h \
    button.h \
    operationpanel.h \
    card.h \
    gameevent.h \
    playeritem.h \
    player.h \
    event.h \
    seat.h \
    widgets.h

RESOURCES += \
    sgs.qrc
