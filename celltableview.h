#ifndef CELLTABLEVIEW_H
#define CELLTABLEVIEW_H

#include <QGraphicsScene>
#include <QList>
#include <QObject>
#include <QGraphicsLineItem>
#include <QVector>
#include "cellview.h"
class CellTableView: public QObject
{
    Q_OBJECT
public:
    explicit CellTableView(int rows = 5, int columns = 5, qreal cellSize = 50, QGraphicsScene * scene = nullptr);
    void setRows(int newRows);
    void setColumns(int newColumns);
    void repaintTable(QVector<QPoint> blockedCells);
public slots:
    void blockedCellChanged(int row, int col);
    void onPointAApplied(int row, int col);
    void onPointBApplied(int row, int col);
    void onPathFound(QVector<QPoint>);
    void onPointsClear();
signals:
    void cellSelectedAsBlocked(int row, int col);
    void cellSelectedAsPoint(int row, int col);
private:
    int rows;
    int columns;
    qreal cellSize;
    QGraphicsScene *scene;
    QVector<QVector<CellView*>> cellsMatrix;
    QList<QGraphicsLineItem*> pathLines;
    CellView *pointA;
    CellView *pointB;
    void clearPath();
    void clearCells();
};

#endif // CELLTABLEVIEW_H
