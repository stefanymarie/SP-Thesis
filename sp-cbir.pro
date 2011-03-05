#-------------------------------------------------
#
# Project created by QtCreator 2011-03-05T02:33:17
#
#-------------------------------------------------

QT      += core gui
QT			+= opengl
QT			+= sql

CONFIG  += thread
CONFIG	+= qvopencv

TARGET		= sp-cbir
TEMPLATE	= app

INCLUDEPATH += C:/OpenCV2.2MinGW/include
LIBS				+= C:/OpenCV2.2MinGW/bin/*.dll

SOURCES	+=	main.cpp\
						mainwindow.cpp \
						dbconnect.cpp \
						slots.cpp \
						qtopencv.cpp

HEADERS	+=	mainwindow.h \
						dbconnect.h

FORMS		+=	mainwindow.ui \
						dbconnect.ui

RESOURCES += \
    resources.qrc
