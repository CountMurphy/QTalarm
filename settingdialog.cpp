#include "settingdialog.h"
#include "ui_settingdialog.h"
#include "fileio.h"

SettingDialog::SettingDialog(QWidget *parent,bool *isMilTime) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    //default button
    _isMilTime=isMilTime;
    ui->plebTime->setChecked(!*_isMilTime);
    ui->milTime->setChecked(*_isMilTime);

    ui->defaultShow->setChecked(FileIO::LoadWindowShow());

    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(Save()));
}

SettingDialog::~SettingDialog()
{
    delete ui;
}


void SettingDialog::Save()
{
    FileIO::SaveWindowShow(ui->defaultShow->isChecked());
    *_isMilTime=ui->milTime->isChecked();
    FileIO::SaveTimeMode(*_isMilTime);
    this->deleteLater();
}
