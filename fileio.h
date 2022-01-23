#ifndef FILEIO_H
#define FILEIO_H

#include "schedules.h"
#include "schedulemodel.h"
#include <QObject>
#include <QSettings>
#include <QList>

class FileIO : public QObject
{
    Q_OBJECT
public:
    explicit FileIO(QObject *parent = 0);
    static bool ExtractAudio();
    static bool DelExtracted();
    QList<ScheduleModel *> LoadConfig();
    bool Save(Schedules*);
    static int LoadVolume();
    static void SaveVolume(int);
    static bool LoadWindowShow();
    static void SaveWindowShow(bool);
    static bool isMilTime();
    static bool LoadisMono();
    static bool LoadSeenSolveText();
    static void SaveisMono(bool);
    static void SaveSeenSolveText();
    static void SaveisMilTime(bool isMilTime);
    static bool LoadWarnOnPm();
    static void SaveWarnOnPm(bool);
private:
    QSettings _Settings;
signals:
    
public slots:
    
};

#endif // FILEIO_H
