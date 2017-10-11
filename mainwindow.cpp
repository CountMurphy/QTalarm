#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timer.h"
#include "alarm.h"
#include "fileio.h"
#include "schedulecollection.h"
#include "aboutdialog.h"
#include "settingdialog.h"
#include "snooze.h"
#include <QMessageBox>
#include <QCheckBox>
#include <QLabel>
#include <QCloseEvent>
#include <QTimeEdit>
#include <QTimer>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QSlider>
#include <QSystemTrayIcon>
#include <QListWidgetItem>
#include <QCalendarWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->_supportsTray = QSystemTrayIcon::isSystemTrayAvailable();
    if(!this->_supportsTray)
    {
        qInfo() << "No system tray detected. What a shitty DE"; //what is this 1993?
    }

    //Create / load Schedule
    _Schedules=new ScheduleCollection(this);
    _Schedules->LoadSchedules();
    PopulateListWidget();
    DisablePanelIfNoSelection();

    _isMilTime=FileIO::isMilTime();
    _WarnOnPm=FileIO::LoadWarnOnPm();
    _prevTimeWasMil=_isMilTime;
    displayTimeMode();

    //Call Time keeper
    TimeKeeper=new Timer(this,_Schedules);
    CurAlarm=new Alarm(this);
    TimeKeeper->StartTimer(CurAlarm);

    //Set Volume
    int Volume = FileIO::LoadVolume();
    ui->VolumeSlider->setValue(Volume<=0? 50:Volume);
    CurAlarm->SetVolume(ui->VolumeSlider->value());
    ui->listAlmBtn->button(QDialogButtonBox::Ok)->setText("&Add");
    ui->listAlmBtn->button(QDialogButtonBox::Cancel)->setText("&Remove");

    trayIcon=new QSystemTrayIcon(this);
    trayIconMenu=new QMenu(this);
    QAction *QAshow=new QAction("&Show",this);
    QAction *QAquit=new QAction("&Quit",this);

    trayIconMenu->addAction(QAshow);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(QAquit);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/new/icons/Clock.png"));
    trayIcon->setToolTip("QTalarm");
    trayIcon->show();

    ui->txtSoundPath->setText("");
    ui->CustEdit->setDate(QDate::currentDate());
    SetupClock();


    //set up ui slots
    connect(QAquit,SIGNAL(triggered()),this,SLOT(Quit()));
    connect(QAshow,SIGNAL(triggered()),this,SLOT(ShowWindow()));
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(ShowWindow(QSystemTrayIcon::ActivationReason)));
    connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(Quit()));
    connect(ui->actionAbout_QT,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
    connect(ui->actionAbout_QTalam,SIGNAL(triggered()),this,SLOT(ShowAbout()));
    connect(ui->actionSettings,SIGNAL(triggered(bool)),this,SLOT(ShowSettings()));
    connect(ui->timeEdit,SIGNAL(editingFinished()),this,SLOT(SetTime()));
    connect(ui->listAlmBtn,SIGNAL(clicked(QAbstractButton*)),this,SLOT(AddRemoveAlarm(QAbstractButton*)));
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(ShowActiveAlarm(int)));
    connect(ui->chkMon,SIGNAL(clicked(bool)),this,SLOT(ToggleMon(bool)));
    connect(ui->chkTues,SIGNAL(clicked(bool)),this,SLOT(ToggleTue(bool)));
    connect(ui->chkWed,SIGNAL(clicked(bool)),this,SLOT(ToggleWed(bool)));
    connect(ui->chkThurs,SIGNAL(clicked(bool)),this,SLOT(ToggleThur(bool)));
    connect(ui->chkFri,SIGNAL(clicked(bool)),this,SLOT(ToggleFri(bool)));
    connect(ui->chkSat,SIGNAL(clicked(bool)),this,SLOT(ToggleSat(bool)));
    connect(ui->chkSun,SIGNAL(clicked(bool)),this,SLOT(ToggleSun(bool)));
    connect(ui->chkCustom,SIGNAL(clicked(bool)),this,SLOT(ToggleCust(bool)));
    connect(ui->chkSounds,SIGNAL(clicked(bool)),this,SLOT(OpenDiaglog(bool)));
    connect(ui->TestBtn,SIGNAL(clicked()),this,SLOT(TestAlarm()));
    connect(ui->VolumeSlider,SIGNAL(valueChanged(int)),CurAlarm,SLOT(SetVolume(int)));

    connect(ui->calendarWidget,SIGNAL(clicked(QDate)),this,SLOT(SetCustomDate()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    event->ignore();
    if(this->_supportsTray)
    {
        this->hide();
    }else{
        Quit();
    }
}

void MainWindow::SetupClock()
{
    //Set up clock display
    QTimer *CurrentTime=new QTimer(this);
    connect(CurrentTime,SIGNAL(timeout()),this,SLOT(timeCheck()));
    CurrentTime->start(500);
}

void MainWindow::ShowWindow(QSystemTrayIcon::ActivationReason Reason)
{
    if(Reason==QSystemTrayIcon::DoubleClick || Reason==QSystemTrayIcon::Trigger)
    {
        ShowWindow();
    }
}

void MainWindow::ShowWindow()
{
    if(this->CurAlarm->isPlaying())
    {
        this->CurAlarm->Stop();
    }
    ui->TestBtn->setText("Test");
    this->show();
}

void MainWindow::SetTime()
{
    if(ui->timeEdit->time().hour()>12 && !_isMilTime && _WarnOnPm)
    {
        PMWarning();
    }
    if(ui->listWidget->currentIndex().column()==-1)
    {
        //There is no selected row. Enter was probably hit, the time registered, folowed by
        //on change trigger, execpt the changes have already been logged
        return;
    }
    Schedule *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->SetTime(ui->timeEdit->time());
    UpdateListWidget();
}

void MainWindow::SetCustomDate()
{
    //Update date on the display
    ui->CustEdit->setDate(ui->calendarWidget->selectedDate());
    Schedule *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->SetTime(ui->timeEdit->time());
    QDate CustomDate=ui->calendarWidget->selectedDate();
    Active->SetCust(CustomDate);
    if(Active->isCustomEnabled())
        UpdateListWidget();
}

void MainWindow::ToggleMon(bool isEnabled)
{
    Schedule *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->setIsMonEnabled(isEnabled);
    UpdateListWidget();
}

void MainWindow::ToggleTue(bool isEnabled)
{
    Schedule *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->setIsTueEnabled(isEnabled);
    UpdateListWidget();
}
void MainWindow::ToggleWed(bool isEnabled)
{
    Schedule *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->setIsWedEnabled(isEnabled);
    UpdateListWidget();
}
void MainWindow::ToggleThur(bool isEnabled)
{
    Schedule *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->setIsThurEnabled(isEnabled);
    UpdateListWidget();
}
void MainWindow::ToggleFri(bool isEnabled)
{
    Schedule *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->setIsFriEnabled(isEnabled);
    UpdateListWidget();
}
void MainWindow::ToggleSat(bool isEnabled)
{
    Schedule *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->setIsSatEnabled(isEnabled);
    UpdateListWidget();
}
void MainWindow::ToggleSun(bool isEnabled)
{
    Schedule *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->setIsSunEnabled(isEnabled);
    UpdateListWidget();
}


void MainWindow::ToggleCust(bool isEnabled)
{
    Schedule *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->SetCustEnabled(isEnabled);
    UpdateListWidget();
}

void MainWindow::Quit()
{
    this->_Schedules->Save();
    FileIO::DelExtracted();
    FileIO::SaveVolume(ui->VolumeSlider->value());
    qApp->quit();
}

void MainWindow::AddRemoveAlarm(QAbstractButton *button)
{
    if(button->text()=="&Add")
    {
        Schedule *scheToAdd=new Schedule(this);
        this->_Schedules->AddSchedule(scheToAdd);
        ui->listWidget->addItem(scheToAdd->Name());
        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    }
    else if(button->text()=="&Remove")
    {
        this->_lastDeletedIndex=ui->listWidget->currentRow();
        this->_Schedules->removeScheduleByIndex(ui->listWidget->currentRow());
        PopulateListWidget();
    }
}



void MainWindow::ShowActiveAlarm(int index)
{
        DisablePanelIfNoSelection();
    if(index==-1)
    {
        //in the middle of a list clear. Running further will cause seg fault
        return;
    }
    Schedule *active=this->_Schedules->GetSchedule(index);
    ui->timeEdit->setTime(active->GetTime());

    ui->chkCustom->setChecked(active->GetCustomEnabled());
    ui->CustEdit->setDate(active->GetCustomDate());
    ui->chkSounds->setChecked(active->GetCustomSoundEnabled());
    ui->txtSoundPath->setText(active->GetCustomSound());

    ui->chkMon->setChecked(active->isMonEnabled());
    ui->chkTues->setChecked(active->isTueEnabled());
    ui->chkWed->setChecked(active->isWedEnabled());
    ui->chkThurs->setChecked(active->isThurEnabled());
    ui->chkFri->setChecked(active->isFriEnabled());
    ui->chkSat->setChecked(active->isSatEnabled());
    ui->chkSun->setChecked(active->isSunEnabled());
    ui->calendarWidget->setSelectedDate(active->GetCustomDate());
}

void MainWindow::timeCheck()
{
    UpdateClock();
    SnoozeMenuCheck();
    if(_isMilTime!=_prevTimeWasMil)
    {
        _prevTimeWasMil=_isMilTime;
        displayTimeMode();
    }
}

void MainWindow::UpdateClock()
{
    if(_isMilTime)
    {
        ui->Clock->setText(QTime::currentTime().toString("H:mm:ss"));
    }else{
        ui->Clock->setText(QTime::currentTime().toString("h:mm:ss ap"));
    }
}


void MainWindow::OpenDiaglog(bool isChecked)
{
    Schedule *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->SetCustomSoundEnabled(isChecked);
    if(isChecked)
    {
        QString AlarmLocation = QFileDialog::getOpenFileName(this,"Select Alarm File",QDir::homePath());
        Active->SetCustomSound(AlarmLocation);
        ui->txtSoundPath->setText(AlarmLocation);
    }else{
        ui->txtSoundPath->setText("");
    }
}

void MainWindow::TestAlarm()
{
    if(ui->TestBtn->text()=="Test" || ui->TestBtn->text()=="&Test")
    {
        if(ui->chkSounds->isChecked())
        {
            this->CurAlarm->SetCustomPath(ui->txtSoundPath->text());
            this->CurAlarm->Start(true);
        }else{
            this->CurAlarm->Start(false);
        }
        ui->TestBtn->setText("Stop");
    }else{
        this->CurAlarm->Stop();
        ui->TestBtn->setText("Test");
    }
}

void MainWindow::ShowAbout()
{
    AboutDialog *aboutbox=new AboutDialog(this);
    aboutbox->show();
}


void MainWindow::SnoozeMenuCheck()
{
    if(this->CurAlarm->isPlaying() && this->CurAlarm->canResume && (ui->TestBtn->text()=="Test" || ui->TestBtn->text()=="&Test"))
    {
        //Create Snooze Menu object
        snooze *snMenu=new snooze(this,CurAlarm);
        snMenu->show();
        if(this->_supportsTray)
        {
            this->hide();
        }
        this->CurAlarm->canResume=false;
    }
}


void MainWindow::PMWarning()
{
    QMessageBox::warning(this,"Time Verification","Your selected time is set for PM. If you intended to wake in the morning, now is your chance to fix it");
}


void MainWindow::ShowSettings()
{
    SettingDialog *settingsPage=new SettingDialog(this,&_isMilTime, &_WarnOnPm);
    settingsPage->show();
}

void MainWindow::displayTimeMode()
{
    if(_isMilTime)
    {
        ui->timeEdit->setDisplayFormat("H:mm:ss");
        ui->CustEdit->setDisplayFormat("d MMM yyyy");
    }else{
        ui->timeEdit->setDisplayFormat("h:mm:ss ap");
        ui->CustEdit->setDisplayFormat("d MMM yyyy");

    }
}

void MainWindow::PopulateListWidget()
{
    ui->listWidget->clear();
    Schedule *sche;
    foreach(sche,this->_Schedules->GetScheduleList())
    {
        ui->listWidget->addItem(sche->Name());
    }
    ui->listWidget->setCurrentRow(this->_lastDeletedIndex);
}

void MainWindow::DisablePanelIfNoSelection()
{
    if(ui->listWidget->currentRow()==-1)
    {
        ui->chkCustom->setEnabled(false);
        ui->chkFri->setEnabled(false);
        ui->chkMon->setEnabled(false);
        ui->chkSat->setEnabled(false);
        ui->chkSounds->setEnabled(false);
        ui->chkSun->setEnabled(false);
        ui->chkThurs->setEnabled(false);
        ui->chkTues->setEnabled(false);
        ui->chkWed->setEnabled(false);
        ui->CustEdit->setEnabled(false);
        ui->timeEdit->setEnabled(false);

        ui->chkCustom->setChecked(false);
        ui->chkFri->setChecked(false);
        ui->chkMon->setChecked(false);
        ui->chkSat->setChecked(false);
        ui->chkSounds->setChecked(false);
        ui->chkSun->setChecked(false);
        ui->chkThurs->setChecked(false);
        ui->chkTues->setChecked(false);
        ui->chkWed->setChecked(false);
        ui->txtSoundPath->setText("");

    }
    else
    {
        ui->chkCustom->setEnabled(true);
        ui->chkFri->setEnabled(true);
        ui->chkMon->setEnabled(true);
        ui->chkSat->setEnabled(true);
        ui->chkSounds->setEnabled(true);
        ui->chkSun->setEnabled(true);
        ui->chkThurs->setEnabled(true);
        ui->chkTues->setEnabled(true);
        ui->chkWed->setEnabled(true);
        ui->CustEdit->setEnabled(true);
        ui->timeEdit->setEnabled(true);
    }
}

void MainWindow::UpdateListWidget()
{
    int index=ui->listWidget->currentRow();
    PopulateListWidget();
    ui->listWidget->setCurrentRow(index);
}
