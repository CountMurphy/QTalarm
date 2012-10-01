#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
 #include <QCloseEvent>


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
        trayIconMenu->addSeparator();
        trayIconMenu->addAction(QAquit);
        trayIcon->setContextMenu(trayIconMenu);
        trayIcon->setIcon(QIcon("Icons/1349069370_Alarm_Clock.png"));
        trayIcon->setToolTip("QTalarm");
        trayIcon->show();

        //set up slots
        connect(QAquit,SIGNAL(triggered()),qApp,SLOT(quit()));
        connect(QAshow,SIGNAL(triggered()),this,SLOT(ShowWindow()));
        connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(ShowWindow(QSystemTrayIcon::ActivationReason)));
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

void MainWindow::closeEvent(QCloseEvent * event)
{
    event->ignore();
    this->hide();
}

void MainWindow::ShowWindow(QSystemTrayIcon::ActivationReason Reason)
{
    if(Reason==QSystemTrayIcon::DoubleClick)
    {
        ShowWindow();
    }
}

void MainWindow::ShowWindow()
{
    this->show();
}
