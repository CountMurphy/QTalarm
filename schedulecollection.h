#ifndef SCHEDULECOLLECTION_H
#define SCHEDULECOLLECTION_H

#include "schedule.h"
#include <QObject>

class ScheduleCollection : public QObject
{
    Q_OBJECT
public:
    explicit ScheduleCollection(QObject *parent = 0);
    Schedule* GetSchedule(int);
    void LoadSchedules();
    void Save();
private:
    Schedule *_Collection[5];
signals:
    
public slots:
    
};

#endif // SCHEDULECOLLECTION_H
