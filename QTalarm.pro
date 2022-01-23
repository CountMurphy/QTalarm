#-------------------------------------------------
#
# Project created by QtCreator 2012-09-30T18:05:49
#
#-------------------------------------------------

QT       += core gui multimedia 

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtalarm
TEMPLATE = app


SOURCES += main.cpp\
    bastardsnooze.cpp \
        mainwindow.cpp \
    schedulemodel.cpp \
    timer.cpp \
    alarm.cpp \
    fileio.cpp \
    schedules.cpp \
    aboutdialog.cpp \
    snooze.cpp \
    settingdialog.cpp

HEADERS  += mainwindow.h \
    bastardsnooze.h \
    schedulemodel.h \
    timer.h \
    alarm.h \
    fileio.h \
    schedules.h \
    aboutdialog.h \
    snooze.h \
    settingdialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    bastardsnooze.ui \
    snooze.ui \
    settingdialog.ui

RESOURCES += \
    Icons.qrc
CONFIG += precompile_header
