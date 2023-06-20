#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include "datamodel.h"
#include "pathfinder.h"
#include <QMessageBox>

enum State {
    SelectPointA,
    SelectPointB,
    CalculatedPath,
};

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
private:
    DataModel * model;
    State state = SelectPointA;
    PathFinder * pathFinder;
    QThread *workerThread;
public slots:
    void onStartGenerate(int width, int height);
    void onBlockedCellSelected(int row, int col);
    void onPointCellSelected(int row, int col);
    void onPathFound(const QVector<QPoint> &pathCells);
signals:
    void dataModelChanged(DataModel *data);
    void blockedCellChanged(int row, int col);
    void pointAApplied(int row, int col);
    void pointBApplied(int row, int col);
    void startPathFinder(const DataModel*);
    void pathFound(const QVector<QPoint>& pathCells);
    void clearPoints();
    void multipleBlockedCellsGenerated(const QVector<QPoint>& blockedCells);
};

#endif // CONTROLLER_H
