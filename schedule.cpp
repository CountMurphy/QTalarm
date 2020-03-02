#include "schedule.h"
#include <QDateTime>
#include <QTime>
#include <QString>

Schedule::Schedule(QObject *parent) :
    QObject(parent)
{
    this->setIsMonEnabled(false);
    this->setIsTueEnabled(false);
    this->setIsWedEnabled(false);
    this->setIsThurEnabled(false);
    this->setIsFriEnabled(false);
    this->setIsSatEnabled(false);
    this->setIsSunEnabled(false);

    this->SetCustEnabled(false);
    this->SetTime(QTime::fromMSecsSinceStartOfDay(0));
    this->_CustomAlarm=QDate::currentDate();
    this->SetCustomSound("");
    this->SetCustomSoundEnabled(false);
    this->SetIsBastard(false);
}

void Schedule::SetCustEnabled(bool isEnabled)
{
    this->setIsCustomEnabled(isEnabled);
}

void Schedule::SetCustomSoundEnabled(bool isEnabled)
{
    this->_isCustomSoundEnabled=isEnabled;
}

void Schedule::SetTime(QTime time)
{
    this->_AlarmTime=time;
}

QTime Schedule::GetTime()
{
    return this->_AlarmTime;
}


void Schedule::SetCust(QDate Date)
{
    this->_CustomAlarm=Date;
}

void Schedule::SetCustomSound(QString SoundPath)
{
    this->_CustomSound=SoundPath;
}

void Schedule::SetIsBastard(bool isBast)
{
    this->_isBastard=isBast;
}

bool Schedule::GetCustomEnabled()
{
    return this->isCustomEnabled();
}

bool Schedule::GetCustomSoundEnabled()
{
    return this->_isCustomSoundEnabled;
}



QDate Schedule::GetCustomDate()
{
    return this->_CustomAlarm;
}

bool Schedule::isBastard() const
{
    return this->_isBastard;
}


QString Schedule::GetCustomSound()
{
    return this->_CustomSound;
}

bool Schedule::isMonEnabled() const
{
    return _isMonEnabled;
}

void Schedule::setIsMonEnabled(bool isMonEnabled)
{
    _isMonEnabled = isMonEnabled;
}

bool Schedule::isTueEnabled() const
{
    return _isTueEnabled;
}

void Schedule::setIsTueEnabled(bool isTueEnabled)
{
    _isTueEnabled = isTueEnabled;
}

bool Schedule::isWedEnabled() const
{
    return _isWedEnabled;
}

void Schedule::setIsWedEnabled(bool isWedEnabled)
{
    _isWedEnabled = isWedEnabled;
}

bool Schedule::isThurEnabled() const
{
    return _isThurEnabled;
}

void Schedule::setIsThurEnabled(bool isThurEnabled)
{
    _isThurEnabled = isThurEnabled;
}

bool Schedule::isFriEnabled() const
{
    return _isFriEnabled;
}

void Schedule::setIsFriEnabled(bool isFriEnabled)
{
    _isFriEnabled = isFriEnabled;
}

bool Schedule::isSatEnabled() const
{
    return _isSatEnabled;
}

void Schedule::setIsSatEnabled(bool isSatEnabled)
{
    _isSatEnabled = isSatEnabled;
}

bool Schedule::isSunEnabled() const
{
    return _isSunEnabled;
}

void Schedule::setIsSunEnabled(bool isSunEnabled)
{
    _isSunEnabled = isSunEnabled;
}

bool Schedule::isCustomEnabled() const
{
    return _isCustomEnabled;
}

void Schedule::setIsCustomEnabled(bool isCustomEnabled)
{
    _isCustomEnabled = isCustomEnabled;
}

bool Schedule::isCustomSoundEnabled() const
{
    return _isCustomSoundEnabled;
}

void Schedule::setIsCustomSoundEnabled(bool isCustomSoundEnabled)
{
    _isCustomSoundEnabled = isCustomSoundEnabled;
}

QString Schedule::Name()
{
    QString name;
    name=this->GetTime().toString()+"  ";

    if(this->isMonEnabled())
        name.append(" M");
    if(this->isTueEnabled())
        name.append(" T");
    if(this->isWedEnabled())
        name.append(" W");
    if(this->isThurEnabled())
        name.append(" Th");
    if(this->isFriEnabled())
        name.append(" F");
    if(this->isSatEnabled())
        name.append(" Sat");
    if(this->isSunEnabled())
        name.append(" Sun");
    if(this->isCustomEnabled())
        name.append("  "+this->_CustomAlarm.toString());
    if(this->isBastard())
        name.append(" Σ");

    return name;
}
