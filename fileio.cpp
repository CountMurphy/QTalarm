#include "fileio.h"
#include "schedule.h"
#include "schedulecollection.h"
#include <QFile>
#include <QDir>
#include <QSettings>
#include <QString>
#include <QDateTime>
#include <QTime>
#include <QList>

FileIO::FileIO(QObject *parent) :
    QObject(parent)
{

}

bool FileIO::ExtractAudio()
{
    if(QFile::copy(":/new/sounds/alarm.ogg", QDir::tempPath()+"/QTalarm.ogg"))
    {
        return true;
    }
    return false;
}

bool FileIO::DelExtracted()
{
    return QFile::remove(QDir::tempPath()+"/QTalarm.ogg");
}

//TODO needs to know how many there were, else loop 5 times
QList<Schedule*> FileIO::LoadConfig()//index was passed here
{
    Schedule *Sched;
    QString Index;
    Index.setNum(index);
    bool WDEnabled=this->_Settings.value(Index+"WDEnabled").toBool();
    QTime WDTime=this->_Settings.value(Index+"WDTime").toTime();
    bool WEEnabled=this->_Settings.value(Index+"WEEnabled").toBool();
    QTime WETime=this->_Settings.value(Index+"WETime").toTime();
    bool CustEnabled=this->_Settings.value(Index+"CustEnabled").toBool();
    QDateTime CustTime=this->_Settings.value(Index+"CustTime").toDateTime();
    bool CustSoundEnabled=this->_Settings.value(Index+"CustomSoundEnabled").toBool();
    QString CustSound=this->_Settings.value(Index+"CustomSound").toString();
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
        CustTime.setDate(QDateTime::currentDateTime().date());
    }
    if(CustSoundEnabled==false)
    {
        CustSound="";
    }
    Sched->SetSchedule(CustEnabled,CustTime,WDEnabled,WDTime,WEEnabled,WETime,CustSoundEnabled,CustSound);
    return Sched;
}

bool FileIO::Save(ScheduleCollection *Collection)
{
    try
    {
        QList<Schedule*> SchedList=Collection->GetScheduleList();
        Schedule *currentSche;
        int index=0;

        foreach(currentSche,SchedList)
        {
            QString IndexStr;
            IndexStr.setNum(index);
            this->_Settings.setValue(IndexStr+"MonEnabled",currentSche->isMonEnabled());
            this->_Settings.setValue(IndexStr+"TueEnabled",currentSche->isTueEnabled());
            this->_Settings.setValue(IndexStr+"WedEnabled",currentSche->isWedEnabled());
            this->_Settings.setValue(IndexStr+"ThurEnabled",currentSche->isThurEnabled());
            this->_Settings.setValue(IndexStr+"FriEnabled",currentSche->isFriEnabled());
            this->_Settings.setValue(IndexStr+"SatEnabled",currentSche->isSatEnabled());
            this->_Settings.setValue(IndexStr+"SunEnabled",currentSche->isSunEnabled());
            this->_Settings.setValue(IndexStr+"Time",currentSche->GetTime());
            this->_Settings.setValue(IndexStr+"CustEnabled",currentSche->GetCustomEnabled());
            this->_Settings.setValue(IndexStr+"CustDate",currentSche->GetCustomDate());
            this->_Settings.setValue(IndexStr+"CustomSoundEnabled",currentSche->GetCustomSoundEnabled());
            this->_Settings.setValue(IndexStr+"CustomSound",currentSche->GetCustomSound());
            this->_Settings.sync();
        }
    }
    catch(...)
    {
        return false;
    }

    return true;
}


int FileIO::LoadVolume()
{
    QSettings settings;
    return settings.value("Volume").toInt();
}

void FileIO::SaveVolume(int vol)
{
    QSettings settings;
    settings.setValue("Volume",vol);
}

bool FileIO::LoadWindowShow()
{
    QSettings settings; //not sure why other methods use static settings. May have to refactor
    return settings.value("ShowWindowDefault").toBool();
}


void FileIO::SaveWindowShow(bool showWindow)
{
    QSettings settings;
    settings.setValue("ShowWindowDefault",showWindow);
}


bool FileIO::isMilTime()
{
    QSettings settings;
    return settings.value("isMilTime").toBool();
}

void FileIO::SaveTimeMode(bool isMilTime)
{
    QSettings settings;
    settings.setValue("isMilTime",isMilTime);
}


bool FileIO::LoadWarnOnPm()
{
    QSettings settings;
    return settings.value("WarnOnPm").toBool();
}

void FileIO::SaveWarnOnPm(bool warn)
{
    QSettings settings;
    settings.setValue("WarnOnPm",warn);
}
