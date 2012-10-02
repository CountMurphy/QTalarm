#ifndef FILEIO_H
#define FILEIO_H

#include <QObject>

class FileIO : public QObject
{
    Q_OBJECT
public:
    explicit FileIO(QObject *parent = 0);
    static bool ExtractAudio();
    static bool DelExtracted();
    static bool ReadConfig();
signals:
    
public slots:
    
};

#endif // FILEIO_H
