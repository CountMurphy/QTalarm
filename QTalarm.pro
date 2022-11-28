#-------------------------------------------------
#
# Project created by QtCreator 2012-09-30T18:05:49
#
#-------------------------------------------------

QT       += core gui multimedia 

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtalarm
TEMPLATE = app


SOURCES += src/bastardsnooze.cpp \
           src/mainwindow.cpp \
           src/schedulemodel.cpp \
           src/timer.cpp \
           src/alarm.cpp \
           src/fileio.cpp \
           src/schedules.cpp \
           src/aboutdialog.cpp \
           src/snooze.cpp \
           src/settingdialog.cpp \
           src/main.cpp

HEADERS += src/bastardsnooze.h \
           src/schedulemodel.h \
           src/timer.h \
           src/alarm.h \
           src/fileio.h \
           src/schedules.h \
           src/aboutdialog.h \
           src/snooze.h \
           src/settingdialog.h \
           src/mainwindow.h

FORMS   += src/aboutdialog.ui \
           src/bastardsnooze.ui \
           src/snooze.ui \
           src/settingdialog.ui \
           src/mainwindow.ui

RESOURCES += \
    Icons.qrc
CONFIG += precompile_header

# build dir
UI_DIR  =     build
MOC_DIR =     build
RCC_DIR =     build
OBJECTS_DIR = build
mytarget.commands += $${QMAKE_MKDIR} build
