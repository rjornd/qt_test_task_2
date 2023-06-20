#include "applicationsettings.h"

ApplicationSettings::ApplicationSettings()
{

}

void ApplicationSettings::saveMainWindowState(const QPoint &pos, const QSize &size)
{
    QSettings settings("Test", "TestTaskApplication");
    settings.beginGroup("MainWindow");
        settings.setValue("pos", pos);
        settings.setValue("size", size);
    settings.endGroup();
}

void ApplicationSettings::restoreMainWindowState(QPoint &pos, QSize &size)
{
    QSize defaultSize = QSize(800,600);
    QSettings settings("Test", "TestTaskApplication");
    settings.beginGroup("MainWindow");
        QSize oldSize = settings.value("size", defaultSize).toSize();
        if (oldSize.width()!=0 && oldSize.height()!=0)
        {
            size.setWidth(oldSize.width());
            size.setHeight(oldSize.height());
        }
        QPoint oldPoint = settings.value("pos", QPoint(0, 0)).toPoint();
        if (oldPoint.x()!=0 && oldPoint.y()!=0)
        {
            pos.setX(oldPoint.x());
            pos.setY(oldPoint.y());
        }
        else { // если настройки нет устанавливаем окно в центр экрана
        QDesktopWidget *desktop = QApplication::desktop();
            int screenWidth = desktop->width();
            int screenHeight = desktop->height();
            int windowWidth = oldSize.width();
            int windowHeight = oldSize.height();
            int x = (screenWidth - windowWidth) / 2;
            int y = (screenHeight - windowHeight) / 2;
            pos.setX(x);
            pos.setY(y);
        }
        settings.endGroup();
}
