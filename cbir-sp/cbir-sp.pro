#-------------------------------------------------
#
# Project created by QtCreator 2011-01-31T21:07:37
#
#-------------------------------------------------

QT       += core gui
QT       += sql

TARGET = cbir-sp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    retrieval.cpp \
    dbconnect.cpp

HEADERS  += mainwindow.h \
    retrieval.h \
    dbconnect.h

FORMS    += mainwindow.ui \
    dbconnect.ui
