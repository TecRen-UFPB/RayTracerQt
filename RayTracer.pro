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
    rtvector.cpp \
    rtscene.cpp \
    rtsampler.cpp \
    rtsample.cpp \
    rtcamera.cpp \
    rtpoint.cpp \
    rtray.cpp \
    rtfilm.cpp \
    rtcolor.cpp \
    rtlocalgeo.cpp

HEADERS  += mainwindow.h \
    rtvector.h \
    rtscene.h \
    rtsampler.h \
    rtsample.h \
    rtcamera.h \
    rtpoint.h \
    rtray.h \
    rtfilm.h \
    rtcolor.h \
    rtlocalgeo.h

FORMS    += mainwindow.ui
