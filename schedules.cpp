#include "schedules.h"
#include "schedulemodel.h"
#include "fileio.h"
#include <QString>
#include <QSettings>

Schedules::Schedules(QObject *parent) :
    QObject(parent){}

void Schedules::LoadSchedules()
{
    FileIO *config=new FileIO(this);
    this->_Collection = config->LoadConfig();
}

ScheduleModel* Schedules::GetSchedule(int Index)
{
    return _Collection[Index];
}

void Schedules::Save()
{
    FileIO * configIO=new FileIO(this);
    configIO->Save(this);
}

QList<ScheduleModel*> Schedules::GetScheduleList()
{
    return this->_Collection;
}

void Schedules::AddSchedule(ScheduleModel *scheToAdd)
{
    this->_Collection.append(scheToAdd);
}

void Schedules::removeScheduleByIndex(int index)
{
    this->_Collection.removeAt(index);
}
