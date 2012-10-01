#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 #include <QSystemTrayIcon>

#include <QMainWindow>

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

private slots:
    void ShowWindow();
    void ShowWindow(QSystemTrayIcon::ActivationReason);
};

#endif // MAINWINDOW_H
