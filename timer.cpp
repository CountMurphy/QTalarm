#include "timer.h"
#include <QTimer>
#include <QDateTime>
#include <QDate>
#include "schedulemodel.h"
#include "schedules.h"
#include "fileio.h"

Timer::Timer(QObject *parent,Schedules *Collection) :
    QObject(parent)
{
    this->_Schedules=Collection;
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
        ScheduleModel *cur_sche;
        foreach(cur_sche,this->_Schedules->GetScheduleList())
        {
            this->_CurAlarm->isBastard=cur_sche->isBastard;
            if(cur_sche->isCustomSoundEnabled)
            {
                this->_CurAlarm->SetCustomPath(cur_sche->CustomSoundPath);
            }

            QDateTime RightNow=QDateTime::currentDateTime();//We're in now, now...
            bool soundAlarm=false;

            if(cur_sche->AlarmTime.hour()==RightNow.time().hour() && cur_sche->AlarmTime.minute()==RightNow.time().minute())
            {
                switch(RightNow.date().dayOfWeek())
                {
                //WeekDay Alarms
                case 1:
                    if(cur_sche->isMonEnabled)
                    {
                        soundAlarm=true;
                    }
                    break;

                case 2:
                    if(cur_sche->isTueEnabled)
                    {
                        soundAlarm=true;
                    }
                    break;

                case 3:
                    if(cur_sche->isWedEnabled)
                    {
                        soundAlarm=true;
                    }
                    break;

                case 4:
                    if(cur_sche->isThurEnabled)
                    {
                        soundAlarm=true;
                    }
                    break;

                case 5:
                    if(cur_sche->isFriEnabled)
                    {
                        soundAlarm=true;
                    }
                    break;
                case 6:
                    if(cur_sche->isSatEnabled)
                    {
                        soundAlarm=true;
                    }
                    break;
                case 7:
                    if(cur_sche->isSunEnabled)
                    {
                        soundAlarm=true;
                    }
                    break;

                }
            }
            //Check for Custom Date Alarms
            if(cur_sche->isCustomAlarmEnabled && cur_sche->CustomAlarm == RightNow.date() &&
                    cur_sche->AlarmTime.minute() == RightNow.time().minute()
                    && cur_sche->AlarmTime.hour() == RightNow.time().hour())
            {
                soundAlarm=true;
            }

            if(soundAlarm)
            {
                //Set Condtion One!
                this->_CurAlarm->Start(cur_sche->isCustomSoundEnabled);
                break;
            }
        }
    }
}

