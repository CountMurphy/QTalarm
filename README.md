QTalarm
=======

[![Actions Status](https://github.com/CountMurphy/QTalarm/workflows/Build/badge.svg)](https://github.com/CountMurphy/QTalarm/actions)

A handy alarm clock program written in QT.

Compilation instructions for Linux and MacOS:
```
qmake
make
make clean
```

Windows users will have to compile the program with the QT creator IDE (or download the binaries off the downloads page).

Screenshots and more information on the [official web page!](https://random-hackery.net/page/qtalarm/)

Features
========

- Unlimited number of customizable alarms

- Can wake up using the default sound, or any of audio / video file of your choosing.

- Custom date alarms

- Completely Cross platform

- Support for one-time alarms

## Linux Build/Install

### Building

1. Ensure the proper dependencies are met
    1. Ensure QT5 is installed on your system. On Arch, the needed packages are `qt5-base` and `qt5-multimedia`
    1. Optionally install `noto-fonts` to be able to properly see Unicode symbols in the alarm list widget
1. In the terminal, type `qmake`. This will create a Makefile
1. Type `make`
 
### Installing

1. Copy the qtalarm binary into `/usr/bin` (`sudo cp qtalarm /usr/bin`).
2. Inside of the source code directory, there is a directory called "Icons." These icons need to be copied with the following commands:
   - `sudo cp 1349069370_Alarm_Clock.png /usr/share/icons/hicolor/48x48/apps/`
   - `sudo cp Icons/1349069370_Alarm_Clock24.png /usr/share/icons/hicolor/24x24/apps/1349069370_Alarm_Clock.png`
   - `sudo cp 1349069370_Alarm_Clock16.png /usr/share/icons/hicolor/16x16/apps/1349069370_Alarm_Clock.png`
3. Last step. We need to create a "Desktop Entry" file to include QTalarm in your systems list of programs. Save the following text into a file called qtalarm.desktop located here /usr/share/applications/qtalarm.desktop

```
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
```
4. QTalarm Should now be installed.

## Waybar users
It is possible to configure QTalarm to launch when clicking on the waybar clock. Such a configuration would launch the application each time the clock was clicked. Normally, when QTalarm has a second instance the duplicate process will shutdown and the main window would be shown on the original process. Configuring waybar to run QTalarm with the `--toggleOnDup` flag should force the application to toggle its main window when a duplicate process is launched.

Licensing
==========
GPL V3

Please Report any bugs to the GitHub page at [https://github.com/CountMurphy/QTalarm](https://github.com/CountMurphy/QTalarm).
