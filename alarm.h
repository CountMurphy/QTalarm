#ifndef ALARM_H
#define ALARM_H

#include <QObject>
#include <QString>
#include <QMediaPlayer>
#include <QTimer>

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
    QMediaPlayer * media;
    QString _DefaultPath;
    QString _CustPath;

    QTimer *_Pause;

    bool _UsingCustomPath;
    bool _isPlaying;
    
signals:
    
public slots:
    void RepeatAllTheThings(QMediaPlayer::MediaStatus);
    void Resume();
    void SetVolume(int);
    
};

#endif // ALARM_H
