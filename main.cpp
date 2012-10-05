#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("QTalarm");
    a.setOrganizationName("QTalarm");
    MainWindow w;
    w.show();
    w.hide();
    return a.exec();
}
