#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timer.h"
#include "alarm.h"
#include "fileio.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QTimeEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(QSystemTrayIcon::isSystemTrayAvailable())
    {
        //Call Time keeper
        TimeKeeper=new Timer(this);
        CurAlarm=new Alarm(this);
        TimeKeeper->StartTimer(CurAlarm);

        trayIcon=new QSystemTrayIcon(this);
        trayIconMenu=new QMenu(this);
        QAction *QAshow=new QAction("&Show",this);
        QAction *QAquit=new QAction("&Quit",this);

        trayIconMenu->addAction(QAshow);
        trayIconMenu->addSeparator();
        trayIconMenu->addAction(QAquit);
        trayIcon->setContextMenu(trayIconMenu);
        trayIcon->setIcon(QIcon(":/new/icons/Clock.png"));
        trayIcon->setToolTip("QTalarm");
        trayIcon->show();

        //set up slots
        connect(QAquit,SIGNAL(triggered()),this,SLOT(Quit()));
        connect(QAshow,SIGNAL(triggered()),this,SLOT(ShowWindow()));
        connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(ShowWindow(QSystemTrayIcon::ActivationReason)));
        connect(ui->WD_Edit,SIGNAL(editingFinished()),this,SLOT(SetWDTime()));
        connect(ui->WE_edit,SIGNAL(editingFinished()),this,SLOT(SetWETime()));
        connect(ui->Cust_Edit,SIGNAL(editingFinished()),this,SLOT(SetCustomTime()));
        connect(ui->chkWeekDays,SIGNAL(clicked(bool)),TimeKeeper,SLOT(ToggleWD(bool)));
        connect(ui->chkWeekEnd,SIGNAL(clicked(bool)),TimeKeeper,SLOT(ToggleWE(bool)));

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
        this->CurAlarm->Stop();
        ShowWindow();
    }
}

void MainWindow::ShowWindow()
{
    this->show();
}

void MainWindow::SetWDTime()
{
    if(ui->chkWeekDays->isChecked())
    {
        TimeKeeper->SetWDTime(ui->WD_Edit->time());
    }
}

void MainWindow::SetWETime()
{
    if(ui->chkWeekEnd->isChecked())
    {
        TimeKeeper->SetWETime(ui->WE_edit->time());
    }
}

void MainWindow::SetCustomTime()
{
    if(ui->chkCustom->isChecked())
    {
        QDateTime tempTime;
        tempTime.setTime(ui->Cust_Edit->time());
        tempTime.setDate(ui->calendarWidget->selectedDate());
        TimeKeeper->SetCustomTime(tempTime);
    }
}

void MainWindow::Quit()
{
    FileIO::DelExtracted();
    qApp->quit();
}
