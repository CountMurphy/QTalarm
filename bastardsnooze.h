#ifndef BASTARDSNOOZE_H
#define BASTARDSNOOZE_H

#include <QMainWindow>
#include "alarm.h"
#include "schedules.h"

namespace Ui {
class BastardSnooze;
}

class BastardSnooze : public QMainWindow
{
    Q_OBJECT

public:
    explicit BastardSnooze(QWidget *parent = nullptr, Alarm * curAlarm=0, Schedules * schedule_list=0);
    ~BastardSnooze();

private:
    Ui::BastardSnooze *ui;
    qint32 val1;
    qint32 val2;
    qint32 randOp;
    Alarm * _curAlarm;
    Schedules * _schdule_list;
    void closeEvent(QCloseEvent*);
private slots:
    void checkMath();
};

#endif // BASTARDSNOOZE_H
