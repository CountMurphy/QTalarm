#include "timer.h"
#include <QTimer>
#include <QDateTime>
#include <QDate>
#include "schedule.h"
#include "schedulecollection.h"
#include "fileio.h"

Timer::Timer(QObject *parent,ScheduleCollection *Collection) :
    QObject(parent)
{
    for(int i=0;i<5;i++)
    {
        this->_Schedules[i]=Collection->GetSchedule(i);
        if(this->_Schedules[i]==NULL)
        {
            this->_Schedules[i]=new Schedule(this);
        }
    }
}

void Timer::StartTimer(Alarm *MainAlarm)
{
    this->_CurAlarm=MainAlarm;
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(AlarmCheck()));
    timer->start(10000);
}

void Timer::AlarmCheck()
{
    //Compare saved times with now time
    if(!this->_CurAlarm->isPlaying())
    {
        for(int i=0;i<5;i++)
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
                if(this->_Schedules[i]->GetWDEnabled() && this->_Schedules[i]->GetWD().hour()==RightNow.time().hour() &&
                        this->_Schedules[i]->GetWD().minute()==RightNow.time().minute())
                {
                    //Set Condtion One!
                    this->_CurAlarm->Start();
                }
                break;
            default:
                //WeekEnds
                if(this->_Schedules[i]->GetWEEnabled() && this->_Schedules[i]->GetWE().hour()==RightNow.time().hour() &&
                        this->_Schedules[i]->GetWE().minute()==RightNow.time().minute())
                {
                    //Set Condtion One!
                    this->_CurAlarm->Start();
                }
            }
            //Check for Custom Date Alarms
            if(this->_Schedules[i]->GetCustomEnabled() && this->_Schedules[i]->GetCustom().date()==RightNow.date() &&
                    this->_Schedules[i]->GetCustom().time().minute()==RightNow.time().minute()
                    && this->_Schedules[i]->GetCustom().time().hour()==RightNow.time().hour())
            {
                //Set Conditon One!
                this->_CurAlarm->Start();
            }
        }
    }
}




