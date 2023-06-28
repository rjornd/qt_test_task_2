#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QVector>
#include <QPoint>
#include <QDateTime>
#include <QRandomGenerator>
#include "cellmodel.h"

class DataModel
{
public:
    DataModel(int rows = 5, int columns = 5);
    bool reconstructModel(int rows, int columns);
    bool changeBlockedAtRowColumn(int row, int col);
    void generateRandomBlockedCells();
    int getRows() const;
    int getColumns() const;
    void setPointA(QPoint newPointA);
    QPoint getPointA() const;
    void setPointB(QPoint newPointB);
    QPoint getPointB() const;
    const CellModel* getCell(int row, int col) const;
    const CellModel* getStartCell() const;
    const CellModel* getEndCell() const;
    const QVector<QVector<CellModel *>> &getCells() const;

    const QVector<QPoint> &getBlockedCells() const;
    void setAllCellsToUnlocked();
private:
    QVector<QVector<CellModel*>> cells;
    QVector<QPoint> blockedCells;
    int rows;
    int columns;
    QPoint pointA = QPoint(0,0);
    QPoint pointB = QPoint(0,0);
};

#endif // DATAMODEL_H
