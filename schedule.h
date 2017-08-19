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
    void SetCustEnabled(bool);
    void SetTime(QTime);
    void SetCust(QDate);
    void SetCustomSound(QString);
    void SetCustomSoundEnabled(bool);

    bool GetCustomEnabled();
    bool GetCustomSoundEnabled();

    QTime GetTime();
    QDate GetCustomDate();
    QString GetCustomSound();
    int Index;

    bool isMonEnabled() const;
    void setMonEnabled(bool MonEnabled);

    bool isTueEnabled() const;
    void setTueEnabled(bool TueEnabled);

    bool isWedEnabled() const;
    void setWedEnabled(bool WedEnabled);

    bool isThurEnabled() const;
    void setThurEnabled(bool ThurEnabled);

    bool isFriEnabled() const;
    void setFriEnabled(bool FriEnabled);

    bool isSatEnabled() const;
    void setSatEnabled(bool SatEnabled);

    bool isSunEnabled() const;
    void setSunEnabled(bool SunEnabled);

private:
    QTime _AlarmTime;
    QDate _CustomAlarm;
    QString _CustomSound;
    bool _MonEnabled;
    bool _TueEnabled;
    bool _WedEnabled;
    bool _ThurEnabled;
    bool _FriEnabled;
    bool _SatEnabled;
    bool _SunEnabled;
    bool _CustomEnabled;
    bool _CustomSoundEnabled;
    
signals:
    
public slots:
    
};

#endif // SCHEDULE_H
