#-------------------------------------------------
#
# Project created by QtCreator 2013-12-17T23:19:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RayTracer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rtbuffer.cpp \
    rtvector.cpp

HEADERS  += mainwindow.h \
    rtbuffer.h \
    rtvector.h

FORMS    += mainwindow.ui
