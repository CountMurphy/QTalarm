#include "alarm.h"
#include "fileio.h"
#include <QMediaPlayer>
#include <QString>
#include <QDir>


Alarm::Alarm(QObject *parent) :
    QObject(parent)
{
    media = new QMediaPlayer(this);
    media->setVolume(25);
    
    this->_DefaultPath=QDir::tempPath()+"/QTalarm.wav";
    this->_isPlaying=false;
    this->_Pause=new QTimer(this);
    this->_ManualStop=false;

    connect(this->_Pause,SIGNAL(timeout()),this,SLOT(Resume()));
}

void Alarm::Start(bool useCustom)
{
    if(useCustom)
    {
        media->setMedia(QUrl::fromLocalFile(this->_CustPath));
        this->_UsingCustomPath=true;
    }else{
     FileIO::ExtractAudio();
     media->setMedia(QUrl::fromLocalFile(this->_DefaultPath));
     this->_UsingCustomPath=false;
    }
    media->play();
    connect(media,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(RepeatAllTheThings(QMediaPlayer::State)));
    this->_isPlaying=true;
}

void Alarm::Stop()
{
    this->_ManualStop=true;
    media->stop();
    this->_Pause->start(60000);
}

void Alarm::RepeatAllTheThings(QMediaPlayer::State state)
{
    if(state==QMediaPlayer::StoppedState && this->_ManualStop==false)
    {
        if(this->_UsingCustomPath)
        {
             media->setMedia(QUrl::fromLocalFile(this->_CustPath));
        }else{
             media->setMedia(QUrl::fromLocalFile(this->_DefaultPath));
        }
        media->play();
    }
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
