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
        QAction *QAshow=new QAction("&Show",this);
        QAction *QAquit=new QAction("&Quit",this);

        trayIconMenu->addAction(QAshow);
        trayIconMenu->addAction(QAquit);
        trayIcon->setContextMenu(trayIconMenu);
        trayIcon->setIcon(QIcon("Icons/1349069370_Alarm_Clock.png"));
        trayIcon->setToolTip("QTalarm");
        trayIcon->show();

        //set up slots
        connect(QAquit,SIGNAL(triggered()),qApp,SLOT(quit()));


        connect(QAshow,SIGNAL(triggered()),this,SLOT(ShowWindow()));
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


void MainWindow::ShowWindow()
{
    this->show();
}
