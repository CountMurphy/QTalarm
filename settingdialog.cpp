#include <QSystemTrayIcon>
#include "settingdialog.h"
#include "ui_settingdialog.h"
#include "fileio.h"

SettingDialog::SettingDialog(QWidget *parent,bool *isMilTime, bool *WarnOnPm, QSystemTrayIcon *trayIcon) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    _isMilTime=isMilTime;
    _WarnOnPm=WarnOnPm;
    _trayIcon=trayIcon;

    if(*_isMilTime)
    {
        ui->WarnBox->setDisabled(true);
    }
    ui->WarnBox->setChecked(*WarnOnPm);

    ui->plebTime->setChecked(!*_isMilTime);
    ui->milTime->setChecked(*_isMilTime);

    ui->defaultShow->setChecked(FileIO::LoadWindowShow());
    ui->chk_mono->setChecked(FileIO::LoadisMono());

    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(Save()));
    connect(ui->plebTime,SIGNAL(clicked(bool)),this,SLOT(toggleWarnBox()));
    connect(ui->milTime,SIGNAL(clicked(bool)),this,SLOT(toggleWarnBox()));
}

SettingDialog::~SettingDialog()
{
    delete ui;
}


void SettingDialog::Save()
{
    FileIO::SaveWindowShow(ui->defaultShow->isChecked());
    *_isMilTime=ui->milTime->isChecked();
    *_WarnOnPm=ui->WarnBox->isChecked();
    FileIO::SaveisMilTime(*_isMilTime);
    FileIO::SaveWarnOnPm(*_WarnOnPm);
    FileIO::SaveisMono(ui->chk_mono->isChecked());
    if(ui->chk_mono->isChecked())
    {
        _trayIcon->setIcon(QIcon(":/new/icons/mono.png"));
    }else{
        _trayIcon->setIcon(QIcon(":/new/icons/Clock.png"));
    }
    this->deleteLater();
}

void SettingDialog::toggleWarnBox()
{
    if(ui->plebTime->isChecked())
    {
        ui->WarnBox->setDisabled(false);
    }else{
        ui->WarnBox->setDisabled(true);
    }
}
