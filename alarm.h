#ifndef ALARM_H
#define ALARM_H

#include <QObject>
#include <QString>
#include <phonon/MediaObject>

class Alarm : public QObject
{
    Q_OBJECT
public:
    explicit Alarm(QObject *parent = 0);
    void Start();
    void Stop();
private:
    Phonon::MediaObject* media;
    QString Path;
    
signals:
    
public slots:
    void RepeatAllTheThings();
    
};

#endif // ALARM_H
