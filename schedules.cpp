#include "schedules.h"
#include "schedulemodel.h"
#include "fileio.h"
#include <QString>
#include <QSettings>
#include <QDebug>

Schedules::Schedules(QObject *parent) :
    QObject(parent){}

void Schedules::LoadSchedules()
{
    FileIO *config=new FileIO(this);
    this->_Collection = config->LoadConfig();
}

ScheduleModel* Schedules::GetSchedule(int Index)
{
    return _Collection[Index];
}

void Schedules::Save()
{
    FileIO * configIO=new FileIO(this);
    configIO->Save(this);
}

QList<ScheduleModel*> Schedules::GetScheduleList()
{
    return this->_Collection;
}

void Schedules::AddSchedule(ScheduleModel *scheToAdd)
{
    qInfo() << "Adding new alarm";
    this->_Collection.append(scheToAdd);
    // set index for newly added schedule
    scheToAdd->Index = this->_Collection.size() - 1;
}

void Schedules::removeScheduleByIndex(int index)
{
    qInfo() << "Removing alarm";
    this->_Collection.removeAt(index);
    // reindex remaining schedules after removal
    Reindex();
}

void Schedules::Reindex()
{
    for (int i = 0; i < this->_Collection.size(); ++i)
    {
        this->_Collection[i]->Index = i;
    }
}

void Schedules::MoveRange(int start, int end, int destinationRow)
{
    if (start < 0 || end >= _Collection.size() || start > end)
        return;
    int count = end - start + 1;
    int to = destinationRow;
    // Adjust destination index when moving within the same list
    if (to > start)
        to -= count;
    if (to < 0) to = 0;
    if (to > _Collection.size() - count) to = _Collection.size() - count;

    // Extract the block
    QList<ScheduleModel*> block;
    block.reserve(count);
    for (int i = start; i <= end; ++i)
        block.append(_Collection[i]);
    // Remove the block from original position
    for (int i = 0; i < count; ++i)
        _Collection.removeAt(start);
    // Insert block at new position preserving order
    for (int i = 0; i < count; ++i)
        _Collection.insert(to + i, block[i]);

    // update indices
    Reindex();
}
