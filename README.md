QTalarm
=======

A handy alarm clock Program written in QT.

Compile Instrustions for Linux and Mac:
  Type: "qmake", "make", and then "make clean"

Windows users will have to compile the program with the QT creator IDE (or download the binaries off the downloads page)

Screen shots and more information on the [offical web page!](https://random-hackery.net/page/qtalarm/)

Features
========

- Unlimted number of customizable alarms

- Can wake up using the default sound, or any of audio / video file of your choosing.

- Custom Date alarms

- Completely Cross plateform

Linux Build/Install

Building
You need QT5 installed on your system first.
-cd into the directory with the QTAlarm source files.
-In the termnal, type "qmake" This will create a "Makefile"
-type "make" When done, a new file called "qtalarm" should have been created. This is application itself. You can test it by typing "./qtalarm" in your terminal. The application should run. There will not be any entries for it in your start menu (or whatever that is called in your desktop environment at this point).

Installing

-copy qtalarm into /usr/bin (sudo cp qtalarm /usr/bin).
-inside of the source code directory, there is a directory called "Icons." These icons need to be copied with the following commands:
-sudo cp 1349069370_Alarm_Clock.png /usr/share/icons/hicolor/48x48/apps/
-sudo cp Icons/1349069370_Alarm_Clock24.png /usr/share/icons/hicolor/24x24/apps/1349069370_Alarm_Clock.png
-sudo cp 1349069370_Alarm_Clock16.png /usr/share/icons/hicolor/16x16/apps/1349069370_Alarm_Clock.png
-Last step. We need to create a "Desktop Entry" file to include QTalarm in your systems list of programs. Save the following text into a file called qtalarm.desktop located here /usr/share/applications/qtalarm.desktop

[Desktop Entry]
Encoding=UTF-8
Value=1.0
Type=Application
Name=QTalarm
GenericName=QTalarm
Comment= A nifty alarm clock written in QT
Icon=1349069370_Alarm_Clock.png
Exec=qtalarm
Categories=Application;Utility;



Licensing
==========
GPL V3


Please Report any bugs to the github page at https://github.com/CountMurphy/QTalarm
