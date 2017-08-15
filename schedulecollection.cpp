#include "schedulecollection.h"
#include "schedule.h"
#include "fileio.h"
#include <QString>
#include <QSettings>

ScheduleCollection::ScheduleCollection(QObject *parent) :
    QObject(parent)
{
    //Initialize
//    for(int i=0;i<5;i++)
//    {
//        this->_Collection[i]=new Schedule(this);
//    }
}

//not sure if this will even work
void ScheduleCollection::LoadSchedules()
{
    FileIO *config=new FileIO(this);
//    Schedule item;
//    foreach(item,this->_Collection)
//    {
        this->_Collection = config->LoadConfig();
//    }
}

Schedule ScheduleCollection::GetSchedule(int Index)
{
    return this->_Collection[Index];
}

void ScheduleCollection::Save()
{
    FileIO * configIO=new FileIO(this);
    configIO->Save(this);
}
