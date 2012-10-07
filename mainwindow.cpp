#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timer.h"
#include "alarm.h"
#include "fileio.h"
#include "schedulecollection.h"
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
        //Create / load Schedule
        _Schedules=new ScheduleCollection(this);
        _Schedules->LoadSchedules();
        //Call Time keeper
        TimeKeeper=new Timer(this,_Schedules);
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

        ui->Alm1->setChecked(true);
        SetAlarmNumber();

        //set up slots
        connect(QAquit,SIGNAL(triggered()),this,SLOT(Quit()));
        connect(QAshow,SIGNAL(triggered()),this,SLOT(ShowWindow()));
        connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(ShowWindow(QSystemTrayIcon::ActivationReason)));
        connect(ui->WD_Edit,SIGNAL(editingFinished()),this,SLOT(SetWDTime()));
        connect(ui->WE_edit,SIGNAL(editingFinished()),this,SLOT(SetWETime()));
        connect(ui->Cust_Edit,SIGNAL(editingFinished()),this,SLOT(SetCustomTime()));
        connect(ui->Alm1,SIGNAL(clicked()),this,SLOT(SetAlarmNumber()));
        connect(ui->Alm2,SIGNAL(clicked()),this,SLOT(SetAlarmNumber()));
        connect(ui->Alm3,SIGNAL(clicked()),this,SLOT(SetAlarmNumber()));
        connect(ui->Alm4,SIGNAL(clicked()),this,SLOT(SetAlarmNumber()));
        connect(ui->Alm5,SIGNAL(clicked()),this,SLOT(SetAlarmNumber()));
        connect(ui->chkWeekDays,SIGNAL(clicked(bool)),this,SLOT(ToggleWD(bool)));
        connect(ui->chkWeekEnd,SIGNAL(clicked(bool)),this,SLOT(ToggleWE(bool)));
        connect(ui->chkCustom,SIGNAL(clicked(bool)),this,SLOT(ToggleCust(bool)));


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
    Schedule *Active=this->_Schedules->GetSchedule(this->_CurrentAlarm);
    Active->SetWD(ui->WD_Edit->time());
}

void MainWindow::SetWETime()
{
    Schedule *Active=this->_Schedules->GetSchedule(this->_CurrentAlarm);
    Active->SetWE(ui->WE_edit->time());
}

void MainWindow::SetCustomTime()
{
    Schedule *Active=this->_Schedules->GetSchedule(this->_CurrentAlarm);
    Active->SetCust(ui->Cust_Edit->dateTime());
}

void MainWindow::ToggleWD(bool isEnabled)
{
    Schedule *Active=this->_Schedules->GetSchedule(this->_CurrentAlarm);
    Active->SetWDEnabled(isEnabled);
}

void MainWindow::ToggleWE(bool isEnabled)
{
    Schedule *Active=this->_Schedules->GetSchedule(this->_CurrentAlarm);
    Active->SetWEEnabled(isEnabled);
}

void MainWindow::ToggleCust(bool isEnabled)
{
    Schedule *Active=this->_Schedules->GetSchedule(this->_CurrentAlarm);
    Active->SetCustEnabled(isEnabled);
}

void MainWindow::Quit()
{
    this->_Schedules->Save();
    FileIO::DelExtracted();
    qApp->quit();
}


void MainWindow::SetAlarmNumber()
{
    Schedule *ActiveSchedule;
    int Index;
    if(ui->Alm1->isChecked())
    {
        Index=0;
    }else if(ui->Alm2->isChecked())
    {
        Index=1;
    }else if(ui->Alm3->isChecked())
    {
        Index=2;
    }else if(ui->Alm4->isChecked())
    {
        Index=3;
    }else{
        Index=4;
    }
     this->_CurrentAlarm=Index;

    //display Active

    ActiveSchedule=this->_Schedules->GetSchedule(Index);
    ShowActiveAlarm(ActiveSchedule);
}


void MainWindow::ShowActiveAlarm(Schedule *Active)
{
    ui->chkWeekDays->setChecked(Active->GetWDEnabled());
    ui->WD_Edit->setTime(Active->GetWD());

    ui->chkWeekEnd->setChecked(Active->GetWEEnabled());
    ui->WE_edit->setTime(Active->GetWE());

    ui->chkCustom->setChecked(Active->GetCustomEnabled());
    ui->Cust_Edit->setTime(Active->GetCustom().time());
}
