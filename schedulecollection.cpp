#include "schedulecollection.h"
#include "schedule.h"
#include "fileio.h"
#include <QString>
#include <QSettings>

ScheduleCollection::ScheduleCollection(QObject *parent) :
    QObject(parent){}

void ScheduleCollection::LoadSchedules()
{
    FileIO *config=new FileIO(this);
    this->_Collection = config->LoadConfig();
}

Schedule* ScheduleCollection::GetSchedule(int Index)
{
    return _Collection[Index];
}

void ScheduleCollection::Save()
{
    FileIO * configIO=new FileIO(this);
    configIO->Save(this);
}

QList<Schedule*> ScheduleCollection::GetScheduleList()
{
    return this->_Collection;
}

int ScheduleCollection::GetCount()
{
    return this->_Collection.count();
}

void ScheduleCollection::AddSchedule(Schedule *scheToAdd)
{
    this->_Collection.append(scheToAdd);
}

void ScheduleCollection::removeScheduleByIndex(int index)
{
    this->_Collection.removeAt(index);
}
