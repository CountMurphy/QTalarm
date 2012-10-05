#include "schedule.h"
#include <QDateTime>
#include <QTime>

Schedule::Schedule(QObject *parent) :
    QObject(parent)
{
    this->_WDEnabled=false;
    this->_WEEnabled=false;
    this->_CustomEnabled=false;
}


void Schedule::SetSchedule(bool CustomEnabled,QDateTime CustTime,bool WDEnabled,QTime WDTime,bool WEEnabled,QTime WETime)
{
    this->_CustomEnabled=CustomEnabled;
    this->_CustomAlarm=CustTime;
    this->_WDEnabled=WDEnabled;
    this->_WDAlarm=WDTime;
    this->_WEEnabled=WEEnabled;
    this->_WEAlarm=WETime;
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
