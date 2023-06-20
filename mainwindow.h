#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>
#include "cellview.h"
#include "applicationsettings.h"
#include "celltableview.h"
#include "controller.h"
#include "datamodel.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setController(Controller *newController);

signals:
    void startGenerate(int width, int height);
    void cellSelectedAsBlocked(int row, int col);
    void blockedCellChanged(int row, int col);
    void cellSelectedAsPoint(int row, int col);
    void pointAApplied(int row, int col);
    void pointBApplied(int row, int col);
    void pathFound(const QVector<QPoint> &);
    void clearPoints();
private slots:
    void on_generateButton_clicked();
    void onDataModelChanged(DataModel * model);
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Controller *controller;
    CellTableView *table = nullptr;
    qreal cellSize = 50;
    QGraphicsTextItem * startText;
    void initializeTableView(int rows, int columns);
};
#endif // MAINWINDOW_H
