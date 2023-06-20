#include "cellmodel.h"


CellModel::CellModel(int row, int col): row(row), col(col)
{

}

const QList<CellModel *> &CellModel::getNeighbors() const
{
    return neighbors;
}

void CellModel::setNeighbors(const QList<CellModel *> &newNeighbors)
{
    neighbors = newNeighbors;
}

void CellModel::changeBlocked()
{
    blocked = !blocked;
}

bool CellModel::isBlocked() const
{
    return blocked;
}

int CellModel::getRow() const
{
    return row;
}

int CellModel::getCol() const
{
    return col;
}

void CellModel::setBlocked(bool newBlocked)
{
    blocked = newBlocked;
}
