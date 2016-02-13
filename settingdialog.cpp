#include "settingdialog.h"
#include "ui_settingdialog.h"
#include "fileio.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

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
}
