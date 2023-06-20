#include "celltableview.h"

CellTableView::CellTableView(int rows, int columns, qreal cellSize, QGraphicsScene *scene) :
     rows(rows), columns(columns), cellSize(cellSize), scene(scene)
{
    repaintTable(QVector<QPoint>());
}

void CellTableView::setRows(int newRows)
{
    rows = newRows;
}

void CellTableView::setColumns(int newColumns)
{
    columns = newColumns;
}

void CellTableView::repaintTable(QVector<QPoint> blockedCells)
{
    //очищаем графическое представление
    clearPath();
    clearCells();

    int id = 0;
    for (int row = 0; row < rows; ++row)  //заполняем графическое поле клетками
    {
        QVector<CellView*> tempRow;
        for (int col = 0; col < columns; ++col)
        {
            qreal x = col * cellSize;
            qreal y = row * cellSize;
            CellView *cell = new CellView(x, y, cellSize, id++, row, col);
            connect(cell, &CellView::cellSelectedAsBlocked, this, &CellTableView::cellSelectedAsBlocked);
            connect(cell, &CellView::cellSelectedAsPoint, this, &CellTableView::cellSelectedAsPoint);
            tempRow.push_back(cell);
            scene->addItem(cell);
        }
        cellsMatrix.push_back(tempRow);
    }
    if(!blockedCells.isEmpty()) //отрисовываем заблокированные клетки
    {
        foreach(QPoint cell, blockedCells)
        {
            blockedCellChanged(cell.x(), cell.y());
        }
    }
}

void CellTableView::blockedCellChanged(int row, int col)
{
    CellView* selectedCell = cellsMatrix.value(row).value(col);
    selectedCell->changeBlocked();
    selectedCell->update();
}

void CellTableView::onPointAApplied(int row, int col)
{
    CellView* selectedCell = cellsMatrix.value(row).value(col);
    selectedCell->setMarkedAsStartPoint(true);
    selectedCell->update();
    pointA = selectedCell;
}

void CellTableView::onPointBApplied(int row, int col)
{
    CellView* selectedCell = cellsMatrix.value(row).value(col);
    selectedCell->setMarkedAsDestinationPoint(true);
    selectedCell->update();
    pointB = selectedCell;
}

void CellTableView::onPathFound(QVector<QPoint> path)
{
    clearPath();

    QPointF prevP = QPointF();
    foreach(QPoint point, path) //отрисовываем линии по центру клеток на пути от А до Б
    {
        int row = point.x();
        int col = point.y();
        QPointF lineP = cellsMatrix.value(row).value(col)->getCentralCoords();
        QGraphicsLineItem * pathLine = new QGraphicsLineItem(QLineF(prevP, lineP));
        pathLine->setPen(QPen(Qt::red));
        pathLines.append(pathLine);
        if (prevP != QPointF())
        {
            scene->addItem(pathLine);
        }
        prevP = lineP;
    }
}

void CellTableView::onPointsClear()
{
    clearPath();
    pointA->setMarkedAsStartPoint(false);
    pointB->setMarkedAsDestinationPoint(false);
}


void CellTableView::clearPath()
{
    if(!pathLines.isEmpty())
    {
        foreach(auto line, pathLines)
        {
            delete line;
        }
        pathLines.clear();
    }
}

void CellTableView::clearCells()
{
    if(!cellsMatrix.isEmpty())
    {
        foreach(auto row, cellsMatrix)
        {
            foreach(CellView *cell, row)
            {
                delete cell;
            }
        }
        cellsMatrix.clear();
    }
}
