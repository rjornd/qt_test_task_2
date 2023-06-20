#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H


#include <QPoint>
#include <QSize>
#include <QSettings>
#include <QDesktopWidget>
#include <QApplication>
class ApplicationSettings
{
public:
    ApplicationSettings();
    static void saveMainWindowState(const QPoint &pos, const QSize &size);
    static void restoreMainWindowState(QPoint &pos, QSize &size);
};
#endif // APPLICATIONSETTINGS_H
