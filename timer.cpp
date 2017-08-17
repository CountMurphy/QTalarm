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
//    for(int i=0;i<5;i++)
//    {
//        this->_Schedules[i]=Collection->GetSchedule(i);
//        if(this->_Schedules[i]==NULL)
//        {
//            this->_Schedules[i]=new Schedule(this);
//        }
//    }
    this->_Schedules=Collection->GetScheduleList();
}

void Timer::StartTimer(Alarm *MainAlarm)
{
    this->_CurAlarm=MainAlarm;
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(AlarmCheck()));
    timer->start(1000);
}

void Timer::AlarmCheck()
{
    //Compare saved times with now time
    if(!this->_CurAlarm->isPlaying() && this->_CurAlarm->canResume)
    {
        Schedule *cur_sche;
        foreach(cur_sche,this->_Schedules)
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
                if(cur_sche->GetWDEnabled() && this->cur_sche->GetWD().hour()==RightNow.time().hour() &&
                        this->cur_sche->GetWD().minute()==RightNow.time().minute())
                {
                    SetCustomSound(i);
                    //Set Condtion One!
                    this->_CurAlarm->Start(this->cur_sche->GetCustomSoundEnabled());
                }
                break;
            default:
                //WeekEnds
                if(this->_Schedules[i]->GetWEEnabled() && this->_Schedules[i]->GetWE().hour()==RightNow.time().hour() &&
                        this->_Schedules[i]->GetWE().minute()==RightNow.time().minute())
                {
                    SetCustomSound(i);
                    //Set Condtion One!
                    this->_CurAlarm->Start(this->_Schedules[i]->GetCustomSoundEnabled());
                }
            }
            //Check for Custom Date Alarms
            if(this->_Schedules[i]->GetCustomEnabled() && this->_Schedules[i]->GetCustom().date()==RightNow.date() &&
                    this->_Schedules[i]->GetCustom().time().minute()==RightNow.time().minute()
                    && this->_Schedules[i]->GetCustom().time().hour()==RightNow.time().hour())
            {
                SetCustomSound(i);
                //Set Conditon One!
                this->_CurAlarm->Start(this->_Schedules[i]->GetCustomSoundEnabled());
            }
        }
    }
}


void Timer::SetCustomSound(int i)
{
    //Set custom Sound path if specified
    if(this->_Schedules[i]->GetCustomSoundEnabled())
    {
        this->_CurAlarm->SetCustomPath(this->_Schedules[i]->GetCustomSound());
    }
}
