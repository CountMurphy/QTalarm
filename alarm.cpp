#include "alarm.h"
#include <phonon/AudioOutput>
#include <phonon/MediaObject>
#include <phonon/MediaSource>
#include <QString>


Alarm::Alarm(QObject *parent) :
    QObject(parent)
{
}

void Alarm::Start()
{
    Phonon::MediaObject* media = new Phonon::MediaObject(this);
    Phonon::createPath(media, new Phonon::AudioOutput(Phonon::MusicCategory, this));
    media->setCurrentSource(Phonon::MediaSource("Sounds/condition_one.wav"));
    media->play();
}
