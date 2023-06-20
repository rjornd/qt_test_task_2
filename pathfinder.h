#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <QObject>
#include <QQueue>
#include <QHash>
#include <QVector>
#include <QList>
#include "datamodel.h"
#include "cellmodel.h"
class PathFinder : public QObject
{
    Q_OBJECT
public:
    explicit PathFinder(QObject *parent = nullptr, const DataModel *model = nullptr);
private:
    const DataModel * dataModel;
    bool taskReady = true;
public slots:
    void findPath();
signals:
    void pathFound(const QVector<QPoint>& pathCells);
};

#endif // PATHFINDER_H
