#include "pathfinder.h"

PathFinder::PathFinder(QObject *parent, const DataModel *model) : QObject(parent), dataModel(model)
{
    mutex = new QMutex();
}

PathFinder::~PathFinder()
{
    delete mutex;
}

void PathFinder::findPath()
{
    mutex->lock();
    const CellModel *beginCell = dataModel->getStartCell();
    const CellModel *endCell = dataModel->getEndCell();

    QVector<QPoint> pathCells;

    // Создаем очередь для обхода в ширину
    QQueue<const CellModel*> queue;
    queue.enqueue(beginCell);

    // Создаем HashMap для отслеживания предыдущих клеток в пути
    QHash<const CellModel*, const CellModel*> previousCells;
    previousCells.insert(beginCell, nullptr);

     // Начинаем обход в ширину
    while (!queue.isEmpty())
    {
     const CellModel *currentCell = queue.dequeue();

     // Если достигнута конечная клетка, завершаем обход
     if (currentCell == endCell)
         break;

     // Получаем всех соседей текущей клетки
     QList<CellModel*> neighbors = currentCell->getNeighbors();

     // Обходим всех соседей
     for (CellModel *neighbor : neighbors)
     {
         // Если сосед не посещен и не является препятствием
         if (!previousCells.contains(neighbor) && !neighbor->isBlocked())
         {
             // Добавляем соседа в очередь и отмечаем его предыдущую клетку
             queue.enqueue(neighbor);
             previousCells.insert(neighbor, currentCell);
         }
     }
    }

    // Восстанавливаем путь от конечной клетки до начальной
    if (previousCells.contains(endCell))
    {
     const CellModel *currentCell = endCell;
     while (currentCell != nullptr)
     {
         pathCells.prepend(QPoint(currentCell->getRow(), currentCell->getCol()));
         currentCell = previousCells.value(currentCell);
     }
    }
    mutex->unlock();
    emit pathFound(pathCells);
}

