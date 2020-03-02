#include "bastardsnooze.h"
#include "ui_bastardsnooze.h"
#include <QRandomGenerator>
#include <QDateTime>
#include <QMessageBox>
#include <QCloseEvent>

BastardSnooze::BastardSnooze(QWidget *parent, Alarm * curAlarm) :
    QMainWindow(parent),
    ui(new Ui::BastardSnooze)
{
    ui->setupUi(this);
    QRandomGenerator *generator=new QRandomGenerator();
    generator->seed(QDateTime::currentSecsSinceEpoch());
    val1 = generator->bounded(13);
    val2 = generator->bounded(13);
    randOp = generator->bounded(3);
    this->ui->num1->setProperty("value",val1);
    this->ui->num2->setProperty("value",val2);
    switch(randOp)
    {
    case 0:
        this->ui->Operator->setText("+");
        break;
    case 1:
        this->ui->Operator->setText("-");
        break;
    case 2:
        this->ui->Operator->setText("X");
        break;
    }

    this->_curAlarm=curAlarm;

    //connect btn
    connect(ui->okbtn,SIGNAL(clicked()),this,SLOT(checkMath()));
    connect(ui->Ans,SIGNAL(returnPressed()),this,SLOT(checkMath()));
}

void BastardSnooze::checkMath()
{
    bool retVal=false;
    switch (randOp) {
    case 0:
        retVal=val1+val2==ui->Ans->text().toInt();
        break;
    case 1:
        retVal=val1-val2==ui->Ans->text().toInt();
        break;
    case 2:
        retVal=val1*val2==ui->Ans->text().toInt();
        break;
    }
    if(retVal)
    {
        this->_curAlarm->Stop();
        this->hide();
        this->~BastardSnooze();
    }else{
        QMessageBox::critical(this,"WRONG","WRONG");
    }
}

BastardSnooze::~BastardSnooze()
{
    delete ui;
    this->deleteLater();
}

void BastardSnooze::closeEvent(QCloseEvent *event)
{
    event->ignore();
    QMessageBox::warning(this,"Nope","you didn't think it was going to be that easy did you?");
}
