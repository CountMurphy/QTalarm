#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QPixmap>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    //set Icon info
    QPixmap  image;
    image.load(":/new/icons/Clock.png");
    ui->lblIcon->setPixmap(image);

    QString InfoText;
    InfoText.append("QTalarm was written by CountMurphy");
    InfoText.append("\n");
    InfoText.append("\n");
    InfoText.append("Please send all bugs &");
    InfoText.append("\n");
    InfoText.append("feature requests to ");
    InfoText.append("the git hub page:");
    InfoText.append("\n");
    ui->lblInfo->setText(InfoText);
    ui->lbllink->setOpenExternalLinks(true);
    ui->lbllink->setText("<a href=https://github.com/CountMurphy/QTalarm>https://github.com/CountMurphy/QTalarm</a>");
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
