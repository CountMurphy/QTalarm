#include "fileio.h"
#include <QFile>
#include <QDir>

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

bool FileIO::ReadConfig()
{
    return false;
}
