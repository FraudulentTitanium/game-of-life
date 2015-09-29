#-------------------------------------------------
#
# Project created by QtCreator 2015-09-16T07:23:07
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameOfLife
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    board.cpp

HEADERS  += mainwindow.h \
    board.h

FORMS    += mainwindow.ui
