#ifndef SCHEDULES_H
#define SCHEDULES_H

#include "schedulemodel.h"
#include <QObject>
#include <QList>

class Schedules : public QObject
{
    Q_OBJECT
public:
    explicit Schedules(QObject *parent = 0);
    ScheduleModel* GetSchedule(int);
    QList<ScheduleModel*> GetScheduleList();
    void AddSchedule(ScheduleModel*);
    void removeScheduleByIndex(int);
    void LoadSchedules();
    void Save();
    // Reorder operations
    void MoveRange(int start, int end, int destinationRow);
    void Reindex();
private:
    QList<ScheduleModel*> _Collection;
signals:
    
public slots:
    
};

#endif // SCHEDULES_H
