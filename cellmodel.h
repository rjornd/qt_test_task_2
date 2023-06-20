#ifndef CELLMODEL_H
#define CELLMODEL_H
#include <QList>

class CellModel
{
public:
    CellModel(int row, int col);
    const QList<CellModel *> &getNeighbors() const;
    void setNeighbors(const QList<CellModel *> &newNeighbors);
    void changeBlocked();

    bool isBlocked() const;

    int getRow() const;

    int getCol() const;

    void setBlocked(bool newBlocked);

private:
   int row;
   int col;
   bool blocked = false;
   QList<CellModel*> neighbors;
};

#endif // CELLMODEL_H
