#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QObject>
#include <QTime>
#include <QDateTime>
#include <QString>

class Schedule : public QObject
{
    Q_OBJECT
public:
    explicit Schedule(QObject *parent = 0);
    void SetSchedule(bool,QDateTime,bool,QTime,bool,QTime,bool,QString);
    void SetWDEnabled(bool);
    void SetWEEnabled(bool);
    void SetCustEnabled(bool);
    void SetWD(QTime);
    void SetWE(QTime);
    void SetCust(QDateTime);
    void SetCustomSound(QString);
    void SetCustomSoundEnabled(bool);

    bool GetWDEnabled();
    bool GetWEEnabled();
    bool GetCustomEnabled();
    bool GetCustomSoundEnabled();

    QTime GetWD();
    QTime GetWE();
    QDateTime GetCustom();
    QString GetCustomSound();
    int Index;

private:
    QTime _WDAlarm;
    QTime _WEAlarm;
    QDateTime _CustomAlarm;
    QString _CustomSound;
    bool _WDEnabled;
    bool _WEEnabled;
    bool _CustomEnabled;
    bool _CustomSoundEnabled;
    
signals:
    
public slots:
    
};

#endif // SCHEDULE_H
