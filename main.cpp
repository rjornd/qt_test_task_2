#include "mainwindow.h"
#include "pathfinder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow userInterface;
    Controller * controller = new Controller();
    userInterface.setController(controller);
    userInterface.show();
    return app.exec();
}
