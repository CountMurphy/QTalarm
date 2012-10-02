#ifndef ALARM_H
#define ALARM_H

#include <QObject>

class Alarm : public QObject
{
    Q_OBJECT
public:
    explicit Alarm(QObject *parent = 0);
    void Start();
    
signals:
    
public slots:
    
};

#endif // ALARM_H
