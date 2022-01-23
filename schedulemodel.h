#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QObject>
#include <QTime>
#include <QDateTime>
#include <QString>

class ScheduleModel : public QObject
{
    Q_OBJECT
public:
    explicit ScheduleModel(QObject *parent = 0);

    QDate CustomAlarm;
    bool isCustomAlarmEnabled;

    QTime AlarmTime;

    int Index;
    bool isBastard;
    bool isMonEnabled;
    bool isTueEnabled;
    bool isWedEnabled;
    bool isThurEnabled;
    bool isFriEnabled;
    bool isSatEnabled;
    bool isSunEnabled;

    QString CustomSoundPath;
    bool isCustomSoundEnabled;

    QString Name();


signals:

public slots:

};

#endif // SCHEDULE_H
