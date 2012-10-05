#include "schedulecollection.h"
#include "schedule.h"
#include "fileio.h"
#include <QString>
#include <QSettings>

ScheduleCollection::ScheduleCollection(QObject *parent) :
    QObject(parent)
{
    //Initialize
    for(int i=0;i<5;i++)
    {
        this->_Collection[i]=new Schedule(this);
    }
}

void ScheduleCollection::LoadSchedules()
{
    FileIO *config=new FileIO(this);
    for(int i=0;i<5;i++)
    {
        this->_Collection[i]=config->LoadConfig(i);
    }
}

Schedule* ScheduleCollection::GetSchedule(int Index)
{
    return this->_Collection[Index];
}

void ScheduleCollection::Save()
{
    FileIO * configIO=new FileIO(this);
    configIO->Save(this);
}
