#include "alarm.h"
#include "fileio.h"
#include <phonon/AudioOutput>
#include <phonon/MediaObject>
#include <phonon/MediaSource>
#include <QString>
#include <QDir>


Alarm::Alarm(QObject *parent) :
    QObject(parent)
{
    media = new Phonon::MediaObject(this);
    Phonon::createPath(media, new Phonon::AudioOutput(Phonon::MusicCategory, this));
    
    this->_DefaultPath=QDir::tempPath()+"/QTalarm.wav";
    this->_isPlaying=false;
    this->_Pause=new QTimer(this);

    connect(this->_Pause,SIGNAL(timeout()),this,SLOT(Resume()));
}

void Alarm::Start(bool useCustom)
{
    if(useCustom)
    {
        media->setCurrentSource(Phonon::MediaSource(this->_CustPath));
        this->_UsingCustomPath=true;
    }else{
     FileIO::ExtractAudio();
     media->setCurrentSource(Phonon::MediaSource(this->_DefaultPath));
     this->_UsingCustomPath=false;
    }
    media->play();
    connect(media,SIGNAL(finished()),this,SLOT(RepeatAllTheThings()));
    this->_isPlaying=true;
}

void Alarm::Stop()
{
    media->stop();
    this->_Pause->start(60000);
}

void Alarm::RepeatAllTheThings()
{
    if(this->_UsingCustomPath)
    {
        media->setCurrentSource(Phonon::MediaSource(this->_CustPath));
    }else{
        media->setCurrentSource(Phonon::MediaSource(this->_DefaultPath));
    }
    media->play();
}

bool Alarm::isPlaying()
{
    return this->_isPlaying;
}

void Alarm::SetCustomPath(QString CustPath)
{
    this->_CustPath=CustPath;
}

void Alarm::Resume()
{
    this->_isPlaying=false;
    this->_Pause->stop();
}
