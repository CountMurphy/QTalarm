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
    void Start(bool);
    void Stop();
    bool isPlaying();
    void SetCustomPath(QString);
private:
    Phonon::MediaObject* media;
    QString _DefaultPath;
    QString _CustPath;
    bool _UsingCustomPath;
    bool _isPlaying;
    
signals:
    
public slots:
    void RepeatAllTheThings();
    
};

#endif // ALARM_H
