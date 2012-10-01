#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(QSystemTrayIcon::isSystemTrayAvailable())
    {
        trayIcon=new QSystemTrayIcon(this);
        trayIconMenu=new QMenu(this);
        trayIconMenu->addAction("Show");
        trayIconMenu->addAction("Quit");
        trayIcon->setContextMenu(trayIconMenu);
        trayIcon->setIcon(QIcon("Icons/1349069370_Alarm_Clock.png"));
        trayIcon->setToolTip("QTalarm");
        trayIcon->show();
    }else{
        //Error out and quit
        QMessageBox::critical(this,"Abort","Unsupported Desktop Environment.  Exiting");
        exit(EXIT_FAILURE);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
