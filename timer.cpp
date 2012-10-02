#include "timer.h"
#include <QTimer>
#include <QDateTime>

Timer::Timer(QObject *parent) :
    QObject(parent)
{
}

void Timer::StartTimer(Alarm *MainAlarm)
{
    this->CurAlarm=MainAlarm;
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(AlarmCheck()));
    timer->start(30000);
}

void Timer::AlarmCheck()
{
    //Compare saved times with now time
}

void Timer::SetWDTime(QTime WDTime)
{
    this->_WDAlarm=WDTime;
}

void Timer::SetWETime(QTime WETime)
{
    this->_WEAlarm=WETime;
}

void Timer::SetCustomTime(QDateTime CustomAlarm)
{
    this->_CustomAlarm=CustomAlarm;
}
