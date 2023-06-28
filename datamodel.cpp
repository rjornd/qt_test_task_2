#include "datamodel.h"

DataModel::DataModel(int rows, int columns): rows(rows), columns(columns)
{
    reconstructModel(rows, columns);
}

bool DataModel::reconstructModel(int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;
    pointA = QPoint(-1,-1);
    pointB = QPoint(-1,-1);
    if(!cells.isEmpty()) // очищаем матрицу клеток если она не пуста
    {
        foreach(auto row, cells)
        {
            foreach(CellModel * cell, row)
            {
                delete cell;
            }
        }
        cells.clear();
    }

    for (int row = 0; row < rows; ++row) //заполняем матрицу клеток
    {
        QVector<CellModel*> tempRow;
        for (int col = 0; col < columns; ++col)
        {
            CellModel *cell = new CellModel(row, col);
            tempRow.push_back(cell);
        }
        cells.push_back(tempRow);
    }

    for (int row = 0; row < rows; ++row) //заполняем соседей для каждой клетки
    {
        for (int col = 0; col < columns; ++col)
        {
            QList<CellModel*> neighbors;
            if(row+1 < rows) neighbors.append(cells.value(row+1).value(col));
            if(row-1 >= 0) neighbors.append(cells.value(row-1).value(col));
            if(col+1 < columns) neighbors.append(cells.value(row).value(col+1));
            if(col-1 >= 0) neighbors.append(cells.value(row).value(col-1));
            cells.value(row).value(col)->setNeighbors(neighbors);
        }
    }
    return true;
}

bool DataModel::changeBlockedAtRowColumn(int row, int col)
{
    if (QPoint(row,col) == pointA || QPoint(row,col) == pointB)
    {
        return false;
    }
    cells.value(row).value(col)->changeBlocked();
    return true;
}

void DataModel::generateRandomBlockedCells()
{
    blockedCells.clear();
    setAllCellsToUnlocked();
    qsrand(QDateTime::currentMSecsSinceEpoch());

    foreach(auto row, cells)
    {
        foreach(CellModel * cell, row)
        {
            double randomValue = qrand() / static_cast<double>(RAND_MAX); //randValue от 0 до 1
            if(randomValue < 0.2) // шанс генерации заблокированной клетки 20%
            {
                cell->setBlocked(true);
                blockedCells.append(QPoint(cell->getRow(), cell->getCol()));
            }
        }
    }
}


int DataModel::getRows() const
{
    return rows;
}

int DataModel::getColumns() const
{
    return columns;
}


QPoint DataModel::getPointA() const
{
    return pointA;
}

void DataModel::setPointA(QPoint newPointA)
{
    pointA = newPointA;
}

QPoint DataModel::getPointB() const
{
    return pointB;
}

void DataModel::setPointB(QPoint newPointB)
{
    pointB = newPointB;
}

const CellModel *DataModel::getCell(int row, int col) const
{
    return cells.value(row).value(col);
}

const CellModel *DataModel::getStartCell() const
{
    int row = pointA.x();
    int col = pointA.y();
    return getCell(row,col);
}

const CellModel *DataModel::getEndCell() const
{
    int row = pointB.x();
    int col = pointB.y();
    return getCell(row,col);
}

const QVector<QVector<CellModel *>> &DataModel::getCells() const
{
    return cells;
}

const QVector<QPoint> &DataModel::getBlockedCells() const
{
    return blockedCells;
}

void DataModel::setAllCellsToUnlocked()
{
    foreach (auto row, cells)
    {
        foreach(CellModel * cell, row)
        {
            cell->setBlocked(false);
        }
    }
}


