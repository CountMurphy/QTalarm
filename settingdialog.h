#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0,bool *isMilTime=0);
    ~SettingDialog();

private:
    Ui::SettingDialog *ui;
    bool *_isMilTime;
private slots:
    void Save();
};

#endif // SETTINGDIALOG_H
