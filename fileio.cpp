#include "fileio.h"
#include "schedule.h"
#include "schedulecollection.h"
#include <QFile>
#include <QDir>
#include <QSettings>
#include <QString>
#include <QDateTime>
#include <QTime>

FileIO::FileIO(QObject *parent) :
    QObject(parent)
{

}

bool FileIO::ExtractAudio()
{
    //Must be a unix if this is reached
    if(QFile::copy(":/new/sounds/alarm.wav", QDir::tempPath()+"/QTalarm.wav"))
    {
        return true;
    }
    return false;
}

bool FileIO::DelExtracted()
{
    return QFile::remove(QDir::tempPath()+"/QTalarm.wav");
}

Schedule* FileIO::LoadConfig(int index)
{
    Schedule *Sched=new Schedule(this);
    QString Index;
    Index.setNum(index);
    bool WDEnabled=this->_Settings.value(Index+"WDEnabled").toBool();
    QTime WDTime=this->_Settings.value(Index+"WDTime").toTime();
    bool WEEnabled=this->_Settings.value(Index+"WEEnabled").toBool();
    QTime WETime=this->_Settings.value(Index+"WETime").toTime();
    bool CustEnabled=this->_Settings.value(Index+"CustEnabled").toBool();
    QDateTime CustTime=this->_Settings.value(Index+"CustTime").toDateTime();
    if(WDTime.isNull())
    {
        WDTime.setHMS(0,0,0,0);
    }
    if(WETime.isNull())
    {
        WETime.setHMS(0,0,0,0);
    }
    if(CustTime.isNull())
    {
        CustTime.time().setHMS(0,0,0,0);
    }
    Sched->SetSchedule(CustEnabled,CustTime,WDEnabled,WDTime,WEEnabled,WETime);
    return Sched;
}

bool FileIO::Save(ScheduleCollection *Collection)
{
    try
    {
        for(int i=0;i<5;i++)
        {
            Schedule *Sched=Collection->GetSchedule(i);
            QString Index;
            Index.setNum(i);
            this->_Settings.setValue(Index+"WDEnabled",Sched->GetWDEnabled());
            this->_Settings.setValue(Index+"WDTime",Sched->GetWD());
            this->_Settings.setValue(Index+"WEEnabled",Sched->GetWEEnabled());
            this->_Settings.setValue(Index+"WETime",Sched->GetWE());
            this->_Settings.setValue(Index+"CustEnabled",Sched->GetCustomEnabled());
            this->_Settings.setValue(Index+"CustTime",Sched->GetCustom());
            this->_Settings.sync();
        }
    }
    catch(...)
    {
        return false;
    }

    return true;
}
