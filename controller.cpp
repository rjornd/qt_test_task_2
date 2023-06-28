#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    model = new DataModel(0, 0);
    pathFinder = new PathFinder(nullptr, model);
    workerThread = new QThread();
    qRegisterMetaType<QVector<QPoint>>("QVector<QPoint>");
    connect(this, &Controller::startPathFinder, pathFinder, &PathFinder::findPath, Qt::QueuedConnection);
    connect(pathFinder, &PathFinder::pathFound, this, &Controller::onPathFound, Qt::QueuedConnection);
    pathFinder->moveToThread(workerThread);
    workerThread->start();
}

Controller::~Controller()
{
    delete workerThread;
    delete pathFinder;
    delete model;
}

void Controller::onStartGenerate(int width, int height)
{
    if (width <= 0 || height <= 0)
    {
        qDebug() << "Неверно указаны ширина/высота";
        return;
    }
    bool ok = model->reconstructModel(height, width);
    if (!ok) {
        QMessageBox::warning(nullptr, "Ошибка", "Модель данных закрыта для записи на время вычисления пути");
        return;
    }
    model->generateRandomBlockedCells();
    model->setPointA(QPoint(-1,-1)); //обнуляем стартовую и конечные точки
    model->setPointB(QPoint(-1,-1));
    state = State::SelectPointA; //возвращаем контроллер в начальное состяние
    emit dataModelChanged(model);
}

void Controller::onBlockedCellSelected(int row, int col)
{
    bool ok = model->changeBlockedAtRowColumn(row, col);
    if (!ok) return;
    emit blockedCellChanged(row, col);
    if (state == State::CalculatedPath) //персчитываем результат при блокировке новой клетки
    {
        emit startPathFinder(model);
    }
}

void Controller::onPointCellSelected(int row, int col)
{
    if(model->getCell(row,col)->isBlocked()) return;
    if(state == State::SelectPointA)
    {
        model->setPointA(QPoint(row,col));
        state = State::SelectPointB;
        emit pointAApplied(row, col);
    } else if (state == State::SelectPointB)
    {
        model->setPointB(QPoint(row,col));
        state = State::CalculatedPath;
        emit pointBApplied(row, col);
        emit startPathFinder(model);
    }
    else if (state == State::CalculatedPath)
    {
        model->setPointA(QPoint(-1,-1));
        model->setPointB(QPoint(-1,-1));
        emit clearPoints();
        state = State::SelectPointA;
    }
}

void Controller::onPathFound(const QVector<QPoint>& pathCells)
{
    emit pathFound(pathCells);
}
