#include "timer.h"
#include <QTimer>
#include <QDateTime>
#include <QDate>

Timer::Timer(QObject *parent) :
    QObject(parent)
{
    this->_WDEnabled=false;
    this->_WEEnabled=false;
}

void Timer::StartTimer(Alarm *MainAlarm)
{
    this->CurAlarm=MainAlarm;
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(AlarmCheck()));
    timer->start(10000);
}

void Timer::AlarmCheck()
{
    //Compare saved times with now time
    if(!this->CurAlarm->isPlaying())
    {
        QDateTime RightNow=QDateTime::currentDateTime();//We're in now, now...
        switch(RightNow.date().dayOfWeek())
        {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                //WeekDay Alarms
                if(this->_WDEnabled && this->_WDAlarm.hour()==RightNow.time().hour() && this->_WDAlarm.minute()==RightNow.time().minute())
                {
                    //Set Condtion One!
                    this->CurAlarm->Start();
                }
                break;
            default:
                //WeekEnds
                if(this->_WEEnabled && this->_WEAlarm.hour()==RightNow.time().hour() && this->_WEAlarm.minute()==RightNow.time().minute())
                {
                    //Set Condtion One!
                    this->CurAlarm->Start();
                }
        }
    }
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

void Timer::ToggleWD(bool value)
{
    this->_WDEnabled= value;
}

void Timer::ToggleWE(bool value)
{
    this->_WEEnabled= value;
}
