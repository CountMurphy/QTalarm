#ifndef SNOOZE_H
#define SNOOZE_H

#include <QDialog>
#include <QTimer>
#include "alarm.h"

namespace Ui {
class snooze;
}

class snooze : public QDialog
{
    Q_OBJECT

public:
    explicit snooze(QWidget *parent = 0,Alarm * curAlarm=0);
    ~snooze();
    bool isDismissed;

public slots:
    void UpdateClock();

private slots:
    void DismissClicked();
    void SnoozeClicked();
    void OtherAlarmCheck();
    void timerOut();

private:
    Ui::snooze *ui;
    void SetupClock();
    Alarm *_curAlarm;
    QTimer *_snoozeTimer;
    QTimer *_otherAlarmCheckTimer;
};

#endif // SNOOZE_H
