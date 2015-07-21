#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T15:25:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = genMdp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    genpassword.cpp

HEADERS  += mainwindow.h \
    random.h \
    genpassword.h

FORMS    += mainwindow.ui
