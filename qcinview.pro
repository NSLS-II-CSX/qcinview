#-------------------------------------------------
#
# Project created by QtCreator 2014-01-20T07:32:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qcinview
TEMPLATE = app

LIBS    += -L../libcin/lib -lcin
INCLUDEPATH += ../libcin/include 
PRE_TARGETDEPS += ../libcin/lib/libcin.a


SOURCES += main.cpp\
        mainwindow.cpp \
    GetImageThread.cpp \
    statuswidget.cpp 

HEADERS  += mainwindow.h \
    GetImageThread.h \
    statuswidget.h 

FORMS    += mainwindow.ui \
    statuswidget.ui
