#include "alarm.h"
#include "fileio.h"
#include <phonon/AudioOutput>
#include <phonon/MediaObject>
#include <phonon/MediaSource>
#include <QString>


Alarm::Alarm(QObject *parent) :
    QObject(parent)
{
    media = new Phonon::MediaObject(this);
    Phonon::createPath(media, new Phonon::AudioOutput(Phonon::MusicCategory, this));
    #ifdef Q_WS_WIN
        this->Path="C:\\Users\\cgugas\\Desktop\\QTalarmTmp.wav";
    #endif
    #ifdef Q_WS_X11
        this->Path="/tmp/QTalarmTmp.wav";
    #endif
    media->setCurrentSource(Phonon::MediaSource(this->Path));
}

void Alarm::Start()
{
    FileIO::ExtractAudio();
    media->play();
    connect(media,SIGNAL(aboutToFinish()),this,SLOT(RepeatAllTheThings()));
}

void Alarm::Stop()
{
    media->stop();
}

void Alarm::RepeatAllTheThings()
{
    media->enqueue(this->Path);
}
