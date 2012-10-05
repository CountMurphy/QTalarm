#-------------------------------------------------
#
# Project created by QtCreator 2012-09-30T18:05:49
#
#-------------------------------------------------

QT       += core gui phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTalarm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    timer.cpp \
    alarm.cpp \
    fileio.cpp \
    schedule.cpp \
    schedulecollection.cpp

HEADERS  += mainwindow.h \
    timer.h \
    alarm.h \
    fileio.h \
    schedule.h \
    schedulecollection.h

FORMS    += mainwindow.ui

RESOURCES += \
    Icons.qrc
