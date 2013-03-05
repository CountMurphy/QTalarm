#ifndef FILEIO_H
#define FILEIO_H

#include "schedulecollection.h"
#include "schedule.h"
#include <QObject>
#include <QSettings>

class FileIO : public QObject
{
    Q_OBJECT
public:
    explicit FileIO(QObject *parent = 0);
    static bool ExtractAudio();
    static bool DelExtracted();
    Schedule* LoadConfig(int);
    bool Save(ScheduleCollection*);
    static int LoadVolume();
    static void SaveVolume(int);
private:
    QSettings _Settings;
signals:
    
public slots:
    
};

#endif // FILEIO_H
