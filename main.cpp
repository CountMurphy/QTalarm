#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("QTalarm");
    MainWindow w;
    w.show();
    w.hide();
    return a.exec();
}
