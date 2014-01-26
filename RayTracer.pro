#-------------------------------------------------
#
# Project created by QtCreator 2013-12-17T23:19:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RayTracer
TEMPLATE = app

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp

SOURCES += main.cpp\
        mainwindow.cpp \
    rtvector.cpp \
    rtscene.cpp \
    rtcamera.cpp \
    rtpoint.cpp \
    rtray.cpp \
    rtfilm.cpp \
    rtcolor.cpp \
    rtsphere.cpp \
    rtraytracer.cpp \
    rtbrdf.cpp \
    rtlight.cpp \
    rtplane.cpp \
    rtchecktexture.cpp


HEADERS  += mainwindow.h \
    rtvector.h \
    rtscene.h \
    rtcamera.h \
    rtpoint.h \
    rtray.h \
    rtfilm.h \
    rtcolor.h \
    rtobject.h \
    rtsphere.h \
    rtraytracer.h \
    rtbrdf.h \
    rtlight.h \
    rtplane.h \
    rtchecktexture.h

FORMS    += mainwindow.ui
