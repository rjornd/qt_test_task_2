#include "mainwindow.h"
#include "ui_mainwindow.h"
#define DEFAULT_CELL_SIZE 50

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), controller(nullptr)
{
    ui->setupUi(this);
    QPoint pos;
    QSize size;
    setWindowTitle("Test task");
    ApplicationSettings::restoreMainWindowState(pos,size);
    this->move(pos);
    this->resize(size);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cellSize = DEFAULT_CELL_SIZE;
    startText = new QGraphicsTextItem("Выберите ширину и высоту поля и нажмите кнопку 'generate'.\n"
                                      "Управление:\n"
                                      "1. ЛКМ-Выбрать точку А/Б/Сбросить точки. \n"
                                      "2. ПКМ-Назначить клетку заблокированной/разблокировать. \n"
                                      "3. Колесико-Масштабировать/Перемещать поле. \n");
    QFont font;
    font.setPointSize(12);
    startText->setFont(font);
    startText->setDefaultTextColor(Qt::red);
    scene->addItem(startText);
}

MainWindow::~MainWindow()
{
    ApplicationSettings::saveMainWindowState(this->pos(), this->size());
    if (table!=nullptr) delete table;
    delete scene;
    delete ui;
}


void MainWindow::on_generateButton_clicked()
{

    int width = ui->widthLineEdit->text().toInt();
    int height = ui->heightLineEdit->text().toInt();
    if (width <= 0 || height <= 0 || width >= 200 || height >= 200) {
        QMessageBox::warning(this, "Ошибка", "Некорректные значения ширины и/или высоты!");
        return;
    }

    if (startText != nullptr)
    {
        scene->removeItem(startText);
        delete startText;
        startText = nullptr;
    }
    int rows = height;
    int columns = width;

    ui->graphicsView->setWidth(width*cellSize);
    ui->graphicsView->setHeight(height*cellSize);
    if (table==nullptr)
    {
        initializeTableView(rows, columns);
    }
    scene->setSceneRect(0, 0, columns*cellSize, rows*cellSize);
    emit startGenerate(width, height);
}

void MainWindow::onDataModelChanged(DataModel *model)
{
    table->setRows(model->getRows());
    table->setColumns(model->getColumns());
    table->repaintTable(model->getBlockedCells());
    ui->graphicsView->setWidth(model->getColumns()*cellSize);
    ui->graphicsView->setHeight(model->getRows()*cellSize);
    scene->setSceneRect(0, 0, model->getColumns()*cellSize, model->getRows()*cellSize);
    ui->graphicsView->setSceneRect(0, 0, model->getColumns()*cellSize, model->getRows()*cellSize);
}

void MainWindow::initializeTableView(int rows, int columns)
{
    table = new CellTableView(rows, columns, 50, scene);
    //signals from view to controller
    connect(table, &CellTableView::cellSelectedAsBlocked, this,
            &MainWindow::cellSelectedAsBlocked);
    connect(table, &CellTableView::cellSelectedAsPoint, this,
            &MainWindow::cellSelectedAsPoint);
    //signals from controller to view
    connect(this, &MainWindow::blockedCellChanged, table,
            &CellTableView::blockedCellChanged);
    connect(this, &MainWindow::pointAApplied, table,
            &CellTableView::onPointAApplied);
    connect(this, &MainWindow::pointBApplied, table,
            &CellTableView::onPointBApplied);
    connect(this, &MainWindow::pathFound, table,
            &CellTableView::onPathFound);
    connect(this, &MainWindow::clearPoints, table,
            &CellTableView::onPointsClear);
}

void MainWindow::setController(Controller *newController)
{
    controller = newController;
    //signals form view to controller
    connect(this, &MainWindow::cellSelectedAsPoint, controller, &Controller::onPointCellSelected);
    connect(this, &MainWindow::cellSelectedAsBlocked, controller, &Controller::onBlockedCellSelected);
    connect(this, &MainWindow::startGenerate, controller, &Controller::onStartGenerate);
    //signals from controller to view
    connect(controller, &Controller::dataModelChanged, this, &MainWindow::onDataModelChanged);
    connect(controller, &Controller::blockedCellChanged, this, &MainWindow::blockedCellChanged);
    connect(controller, &Controller::pointAApplied, this, &MainWindow::pointAApplied);
    connect(controller, &Controller::pointBApplied, this, &MainWindow::pointBApplied);
    connect(controller, &Controller::pathFound, this, &MainWindow::pathFound);
    connect(controller, &Controller::clearPoints, this, &MainWindow::clearPoints);

}

