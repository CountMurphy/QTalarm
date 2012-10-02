#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSystemTrayIcon>
#include <QMainWindow>
#include "timer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    void closeEvent(QCloseEvent*);
    Timer *TimeKeeper;
    Alarm *CurAlarm;

private slots:
    void ShowWindow();
    void ShowWindow(QSystemTrayIcon::ActivationReason);
    void SetWDTime();
    void SetWETime();
    void SetCustomTime();
    void Quit();
};

#endif // MAINWINDOW_H
