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
    Schedules *_Schedules;

    int _lastDeletedIndex=-1;
    bool _isMilTime;
    bool _prevTimeWasMil;
    bool _supportsTray;
    bool _WarnOnPm;
    bool testrun=false;
    void displayTimeMode();
    void LoadOptions();

    void closeEvent(QCloseEvent*);
    void SetupClock();
    void UpdateClock();
    void PMWarning();
    void PopulateListWidget();
    void DisablePanelIfNoSelection();
    void UpdateListWidget();
    void ChangeIconToDefault();
    void SetupSlots(QAction *,QAction *);
    void SetupTrayIcon(QAction *,QAction*);
    void SetupVolume();
    void ConfigureButtons();

    QString solveNotificationTitle = "Solve To Silence";
    QString solveNotification = "Solve to Silence is a new feature that prevents the user from dismissing snooze until they solve a math problem";

private slots:
    void ToggleWindow();
    void ShowActiveAlarm(int index);
    void ToggleWindow(QSystemTrayIcon::ActivationReason);
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
    void ToggleBastard(bool);
    void Quit();
    void OpenDiaglog(bool);
    void TestAlarm();
    void ShowAbout();
    void SnoozeMenuCheck();
    void BastardMenuCheck();
    void timeCheck();
    void ShowSettings();
    void SendTrayMessage(QString title, QString message);
};

#endif // MAINWINDOW_H
