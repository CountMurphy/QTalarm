#include "fileio.h"
#include <QFile>

FileIO::FileIO(QObject *parent) :
    QObject(parent)
{
}

bool FileIO::ExtractAudio()
{
    #ifdef Q_WS_WIN
    //win code
    if(QFile::copy(":/new/sounds/alarm.wav", "C:\\Users\\cgugas\\Desktop\\QTalarmTmp.wav"))
    {
       return true;
    }
    #endif

    //Must be a unix if this is reached
    if(QFile::copy(":/new/sounds/alarm.wav","/tmp/QTalarmTmp.wav"))
    {
        return true;
    }
    return false;
}

bool FileIO::DelExtracted()
{
    #ifdef Q_WS_WIN
    return QFile::remove("C:\\Users\\cgugas\\Desktop\\QTalarmTmp.wav");
    #endif
    return QFile::remove("/tmp/QTalarmTmp.wav");
}

bool FileIO::ReadConfig()
{
    return false;
}
