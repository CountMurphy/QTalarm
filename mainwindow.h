#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSystemTrayIcon>
#include <QMainWindow>
#include <QDialogButtonBox>
#include <QListWidgetItem>
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
    Timer *TimeKeeper;
    Alarm *CurAlarm;
    ScheduleCollection *_Schedules;

    int _lastDeletedIndex;
    bool _isMilTime;
    bool _prevTimeWasMil;
    bool _supportsTray;
    bool _WarnOnPm;
    void displayTimeMode();

    void closeEvent(QCloseEvent*);
    void SetupClock();
    void UpdateClock();
    void PMWarning();
    void PopulateListWidget();
    void DisablePanelIfNoSelection();
    void UpdateListWidget();

private slots:
    void ShowWindow();
    void ShowActiveAlarm(int index);
    void ShowWindow(QSystemTrayIcon::ActivationReason);
    void AddRemoveAlarm(QAbstractButton*);
    void SetTime();
    void SetCustomDate();
    void ToggleMon(bool);
    void ToggleTue(bool);
    void ToggleWed(bool);
    void ToggleThur(bool);
    void ToggleFri(bool);
    void ToggleSat(bool);
    void ToggleSun(bool);
    void ToggleCust(bool);
    void Quit();
    void OpenDiaglog(bool);
    void TestAlarm();
    void ShowAbout();
    void SnoozeMenuCheck();
    void timeCheck();
    void ShowSettings();
};

#endif // MAINWINDOW_H
