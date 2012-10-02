#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QDateTime>

class Timer : public QObject
{
    Q_OBJECT
public:
    static Timer* Instance();
    void StartTimer();
    explicit Timer(QObject *parent = 0);
    void SetWDTime(QTime);
    void SetWETime(QTime);
    void SetCustomTime(QDateTime);
private:
    QTime _WDAlarm;
    QTime _WEAlarm;
    QDateTime _CustomAlarm;
signals:
    
private slots:
    void AlarmCheck();
};

#endif // TIMER_H
