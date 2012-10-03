#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QDateTime>
#include "alarm.h"

class Timer : public QObject
{
    Q_OBJECT
public:
    void StartTimer(Alarm*);
    explicit Timer(QObject *parent = 0);
    void SetWDTime(QTime);
    void SetWETime(QTime);
    void SetCustomTime(QDateTime);
private:
    QTime _WDAlarm;
    QTime _WEAlarm;
    QDateTime _CustomAlarm;
    Alarm *CurAlarm;
    bool _WDEnabled;
    bool _WEEnabled;
signals:
    
public slots:
    void ToggleWD(bool);
    void ToggleWE(bool);
private slots:
    void AlarmCheck();
};

#endif // TIMER_H
