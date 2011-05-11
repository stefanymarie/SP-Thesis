#-------------------------------------------------
#
# Project created by QtCreator 2011-03-26T20:10:48
#
#-------------------------------------------------

QT       += core gui
         += opengl
QT       += sql

CONFIG   += thread
CONFIG   += qvopencv

TARGET   = edgeDetection
TEMPLATE = app

INCLUDEPATH += C:/Programming/OpenCV2.2MinGW/include
LIBS        += C:/Programming/OpenCV2.2MinGW/bin/*.dll

SOURCES  += main.cpp \
            edgedetection.cpp \
            qtopencv.cpp \
            imagedetails.cpp

HEADERS  += edgedetection.h \
            imagedetails.h

FORMS    += edgedetection.ui \
            imagedetails.ui
