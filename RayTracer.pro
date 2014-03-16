#-------------------------------------------------
#
# Project created by QtCreator 2013-12-17T23:19:47
#
#-------------------------------------------------

QT       += core gui script

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
    rtchecktexture.cpp \
    rtlatticenoise.cpp \
    rtturbulencetexture.cpp \
    rtcrisscrosstexture.cpp \
    rtmarbletexture.cpp \
    rtwoodtexture.cpp \
    rtfog.cpp \
    rttriangle.cpp \
    rtsceneloader.cpp \
    startdialog.cpp \
    obj_parser.cpp \
    objLoader.cpp \
    list.cpp \
    string_extra.cpp



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
    rtchecktexture.h \
    rtlatticenoise.h \
    rtturbulencetexture.h \
    rtcrisscrosstexture.h \
    rtmarbletexture.h \
    rtwoodtexture.h \
    rtfog.h \
    rttriangle.h \
    rtsceneloader.h \
    startdialog.h \
    obj_parser.h \
    objLoader.h \
    list.h \
    string_extra.h

FORMS    += mainwindow.ui \
    startdialog.ui
