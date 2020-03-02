#include <QTimer>
#include <QTime>
#include "snooze.h"
#include "alarm.h"
#include "ui_snooze.h"

snooze::snooze(QWidget *parent,Alarm *curAlarm) :
    QDialog(parent),
    ui(new Ui::snooze)
{
    ui->setupUi(this);
    this->_curAlarm=curAlarm;
    this->_snoozeTimer=new QTimer(this);
    this->_otherAlarmCheckTimer=new QTimer(this);
    this->isDismissed=false;
    SetupClock();

    //setup connections
    connect(ui->snzBtn,SIGNAL(clicked()),SLOT(SnoozeClicked()));
    connect(ui->DismissBtn,SIGNAL(clicked()),SLOT(DismissClicked()));
    connect(this->_otherAlarmCheckTimer,SIGNAL(timeout()),SLOT(OtherAlarmCheck()));
    connect(this->_snoozeTimer,SIGNAL(timeout()),SLOT(timerOut()));

}

snooze::~snooze()
{
    delete ui;
}


void snooze::SetupClock()
{
    //Set up clock display
    UpdateClock();
    QTimer *CurrentTime=new QTimer(this);
    connect(CurrentTime,SIGNAL(timeout()),this,SLOT(UpdateClock()));
    CurrentTime->start(500);
}


void snooze::UpdateClock()
{
    ui->time->setText(QTime::currentTime().toString("h:mm:ss ap"));
}


void snooze::SnoozeClicked()
{
    this->_snoozeTimer->start(300000);//5 minutes
    this->_curAlarm->Stop();
    this->_otherAlarmCheckTimer->start(500);
}

void snooze::DismissClicked()
{
    this->_snoozeTimer->stop();
    this->_curAlarm->Stop();
    this->hide();
    this->~snooze();
}

void snooze::timerOut()
{
    this->_otherAlarmCheckTimer->stop();
    this->_curAlarm->Start(this->_curAlarm->UsingCustomPath);
    this->_curAlarm->canResume=false;
    this->_snoozeTimer->stop();
}

void snooze::OtherAlarmCheck()
{
    //If another alarm is playing, destroy this snooze
    if(this->_curAlarm->isPlaying())
    {
        this->hide();
        this->~snooze();
    }
}
