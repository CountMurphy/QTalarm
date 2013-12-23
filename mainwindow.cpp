#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timer.h"
#include "alarm.h"
#include "fileio.h"
#include "schedulecollection.h"
#include "aboutdialog.h"
#include "snooze.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QTimeEdit>
#include <QTimer>
#include <QFileDialog>
#include <QSlider>
#include <QSystemTrayIcon>


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

        //Set Volume
        int Volume = FileIO::LoadVolume();
        ui->VolumeSlider->setValue(Volume<=0? 50:Volume);
        CurAlarm->SetVolume(ui->VolumeSlider->value());

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
        SetupClock();


        //set up ui slots
        connect(QAquit,SIGNAL(triggered()),this,SLOT(Quit()));
        connect(QAshow,SIGNAL(triggered()),this,SLOT(ShowWindow()));
        connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(ShowWindow(QSystemTrayIcon::ActivationReason)));
        connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(Quit()));
        connect(ui->actionAbout_QT,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
        connect(ui->actionAbout_QTalam,SIGNAL(triggered()),this,SLOT(ShowAbout()));
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
        connect(ui->chkSounds,SIGNAL(clicked(bool)),this,SLOT(OpenDiaglog(bool)));
        connect(ui->TestBtn,SIGNAL(clicked()),this,SLOT(TestAlarm()));
        connect(ui->VolumeSlider,SIGNAL(valueChanged(int)),CurAlarm,SLOT(SetVolume(int)));

        connect(ui->calendarWidget,SIGNAL(clicked(QDate)),this,SLOT(SetCustomTime()));


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

void MainWindow::SetupClock()
{
    //Set up clock display
    QTimer *CurrentTime=new QTimer(this);
    connect(CurrentTime,SIGNAL(timeout()),this,SLOT(timeCheck()));
    CurrentTime->start(500);
}

void MainWindow::ShowWindow(QSystemTrayIcon::ActivationReason Reason)
{
    if(Reason==QSystemTrayIcon::DoubleClick || Reason==QSystemTrayIcon::Trigger)
    {
        ShowWindow();
    }
}

void MainWindow::ShowWindow()
{
    if(this->CurAlarm->isPlaying())
    {
        this->CurAlarm->Stop();
    }
    ui->TestBtn->setText("Test");
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
    //Update date on display
    ui->Cust_Edit->setDate(ui->calendarWidget->selectedDate());
    Schedule *Active=this->_Schedules->GetSchedule(this->_CurrentAlarm);
    QDateTime CustomDateTime;
    CustomDateTime.setTime(ui->Cust_Edit->time());
    CustomDateTime.setDate(ui->calendarWidget->selectedDate());
    Active->SetCust(CustomDateTime);
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
    FileIO::SaveVolume(ui->VolumeSlider->value());
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
    ui->Cust_Edit->setDateTime(Active->GetCustom());
    ui->chkSounds->setChecked(Active->GetCustomSoundEnabled());
    ui->txtSoundPath->setText(Active->GetCustomSound());
}

void MainWindow::timeCheck()
{
    UpdateClock();
    SnoozeMenuCheck();
}

void MainWindow::UpdateClock()
{
    ui->Clock->setText(QTime::currentTime().toString("h:mm:ss ap"));
}


void MainWindow::OpenDiaglog(bool isChecked)
{
    Schedule *Active=this->_Schedules->GetSchedule(this->_CurrentAlarm);
    Active->SetCustomSoundEnabled(isChecked);
    if(isChecked)
    {
        QString AlarmLocation = QFileDialog::getOpenFileName(this,"Select Alarm File",QDir::homePath());
        Active->SetCustomSound(AlarmLocation);
        ui->txtSoundPath->setText(AlarmLocation);
    }else{
        ui->txtSoundPath->setText("");
    }
}

void MainWindow::TestAlarm()
{
    if(ui->TestBtn->text()=="Test" || ui->TestBtn->text()=="&Test")
    {
        if(ui->chkSounds->isChecked())
        {
            this->CurAlarm->SetCustomPath(ui->txtSoundPath->text());
            this->CurAlarm->Start(true);
        }else{
            this->CurAlarm->Start(false);
        }
        ui->TestBtn->setText("Stop");
    }else{
        this->CurAlarm->Stop();
        ui->TestBtn->setText("Test");
    }
}

void MainWindow::ShowAbout()
{
    AboutDialog *aboutbox=new AboutDialog(this);
    aboutbox->show();
}


void MainWindow::SnoozeMenuCheck()
{
    if(this->CurAlarm->isPlaying() && this->CurAlarm->canResume && ui->TestBtn->text()=="Test")
    {
        //Create Snooze Menu object
        snooze *snMenu=new snooze(this,CurAlarm);
        snMenu->show();
        this->CurAlarm->canResume=false;
    }
}
