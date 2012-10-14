#include "schedule.h"
#include <QDateTime>
#include <QTime>
#include <QString>

Schedule::Schedule(QObject *parent) :
    QObject(parent)
{
    this->_WDEnabled=false;
    this->_WEEnabled=false;
    this->_CustomEnabled=false;
    this->_WDAlarm.setHMS(0,0,0,0);
    this->_WEAlarm.setHMS(0,0,0,0);
    this->_CustomAlarm.time().setHMS(0,0,0,0);
    this->_CustomSoundEnabled=false;
    this->_CustomSound="";
}


void Schedule::SetSchedule(bool CustomEnabled,QDateTime CustTime,bool WDEnabled,QTime WDTime,bool WEEnabled,QTime WETime,
                           bool CustomSoundEnabled,QString CustomSoundPath)
{
    this->_CustomEnabled=CustomEnabled;
    this->_CustomAlarm=CustTime;
    this->_WDEnabled=WDEnabled;
    this->_WDAlarm=WDTime;
    this->_WEEnabled=WEEnabled;
    this->_WEAlarm=WETime;
    this->_CustomSoundEnabled=CustomSoundEnabled;
    this->_CustomSound=CustomSoundPath;
}

void Schedule::SetWDEnabled(bool isEnabled)
{
    this->_WDEnabled=isEnabled;
}

void Schedule::SetWEEnabled(bool isEnabled)
{
    this->_WEEnabled=isEnabled;
}

void Schedule::SetCustEnabled(bool isEnabled)
{
    this->_CustomEnabled=isEnabled;
}

void Schedule::SetCustomSoundEnabled(bool isEnabled)
{
    this->_CustomSoundEnabled=isEnabled;
}

void Schedule::SetWD(QTime Time)
{
    this->_WDAlarm=Time;
}

void Schedule::SetWE(QTime Time)
{
    this->_WEAlarm=Time;
}

void Schedule::SetCust(QDateTime DateTime)
{
    this->_CustomAlarm=DateTime;
}

void Schedule::SetCustomSound(QString SoundPath)
{
    this->_CustomSound=SoundPath;
}

bool Schedule::GetWDEnabled()
{
    return this->_WDEnabled;
}

bool Schedule::GetWEEnabled()
{
    return this->_WEEnabled;
}

bool Schedule::GetCustomEnabled()
{
    return this->_CustomEnabled;
}

bool Schedule::GetCustomSoundEnabled()
{
    return this->_CustomSoundEnabled;
}

QTime Schedule::GetWD()
{
    return this->_WDAlarm;
}

QTime Schedule::GetWE()
{
    return this->_WEAlarm;
}

QDateTime Schedule::GetCustom()
{
    return this->_CustomAlarm;
}


QString Schedule::GetCustomSound()
{
    return this->_CustomSound;
}
