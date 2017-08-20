#ifndef SCHEDULECOLLECTION_H
#define SCHEDULECOLLECTION_H

#include "schedule.h"
#include <QObject>
#include <QList>

class ScheduleCollection : public QObject
{
    Q_OBJECT
public:
    explicit ScheduleCollection(QObject *parent = 0);
    Schedule* GetSchedule(int);
    QList<Schedule*> GetScheduleList();
    int GetCount();
    void AddSchedule(Schedule*);
    void removeScheduleByIndex(int);
    void LoadSchedules();
    void Save();
private:
    QList<Schedule*> _Collection;
signals:
    
public slots:
    
};

#endif // SCHEDULECOLLECTION_H
