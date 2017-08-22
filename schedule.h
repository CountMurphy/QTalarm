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
    void setIsMonEnabled(bool isMonEnabled);

    bool isTueEnabled() const;
    void setIsTueEnabled(bool isTueEnabled);

    bool isWedEnabled() const;
    void setIsWedEnabled(bool isWedEnabled);

    bool isThurEnabled() const;
    void setIsThurEnabled(bool isThurEnabled);

    bool isFriEnabled() const;
    void setIsFriEnabled(bool isFriEnabled);

    bool isSatEnabled() const;
    void setIsSatEnabled(bool isSatEnabled);

    bool isSunEnabled() const;
    void setIsSunEnabled(bool isSunEnabled);

    bool isCustomEnabled() const;
    void setIsCustomEnabled(bool isCustomEnabled);

    bool isCustomSoundEnabled() const;
    void setIsCustomSoundEnabled(bool isCustomSoundEnabled);

    QString Name();

private:
    QTime _AlarmTime;
    QDate _CustomAlarm;
    QString _CustomSound;
    bool _isMonEnabled;
    bool _isTueEnabled;
    bool _isWedEnabled;
    bool _isThurEnabled;
    bool _isFriEnabled;
    bool _isSatEnabled;
    bool _isSunEnabled;
    bool _isCustomEnabled;
    bool _isCustomSoundEnabled;
    
signals:
    
public slots:
    
};

#endif // SCHEDULE_H
