#include "schedulemodel.h"
#include <QDateTime>
#include <QTime>
#include <QString>

ScheduleModel::ScheduleModel(QObject *parent) :
    QObject(parent)
{
    this->isMonEnabled = false;
    this->isTueEnabled = false;
    this->isWedEnabled = false;
    this->isThurEnabled = false;
    this->isFriEnabled = false;
    this->isSatEnabled = false;
    this->isSunEnabled = false;

    this->isCustomAlarmEnabled = false;
    this->AlarmTime = QTime::fromMSecsSinceStartOfDay(0);
    this->CustomAlarm=QDate::currentDate();
    this->CustomSoundPath = "";
    this->isCustomSoundEnabled = false;
    this->isBastard = false;
}


QString ScheduleModel::Name()
{
    QString name;
    name=this->AlarmTime.toString()+"  ";

    if(this->isMonEnabled)
        name.append(" M");
    if(this->isTueEnabled)
        name.append(" T");
    if(this->isWedEnabled)
        name.append(" W");
    if(this->isThurEnabled)
        name.append(" Th");
    if(this->isFriEnabled)
        name.append(" F");
    if(this->isSatEnabled)
        name.append(" Sat");
    if(this->isSunEnabled)
        name.append(" Sun");
    if(this->isCustomAlarmEnabled)
        name.append("  "+this->CustomAlarm.toString());
    if(this->isBastard)
        name.append(" Σ");

    return name;
}
