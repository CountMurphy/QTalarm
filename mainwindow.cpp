#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timer.h"
#include "alarm.h"
#include "fileio.h"
#include "schedules.h"
#include "aboutdialog.h"
#include "settingdialog.h"
#include "snooze.h"
#include "bastardsnooze.h"
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
#include <QToolTip>
#include <QLocalSocket>
#include <QLocalServer>

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

    TerminateIfRunning();

    //add buttons
    ConfigureButtons();

    //Create / load Schedule
    _Schedules=new Schedules(this);
    _Schedules->LoadSchedules();
    PopulateListWidget();
    DisablePanelIfNoSelection();
    if(ui->listWidget->currentRow()==0)
        ShowActiveAlarm(0);

    LoadOptions();
    toggleOnDuplicateProcess = QApplication::arguments().count() > 1 ? QApplication::arguments().at(1) == "--toggleOnDup":false;

    //Setup threading
    TimeKeeper=new Timer(this,_Schedules);
    //set up alarm singleton
    CurAlarm = &Alarm::GetInstance();
    TimeKeeper->StartTimer(CurAlarm);

    SetupVolume();

    //Tray icons
    QAction *QAshow=new QAction("&Show",this);
    QAction *QAquit=new QAction("&Quit",this);
    SetupTrayIcon(QAshow,QAquit);

    ui->txtSoundPath->setText("");
    ui->CustEdit->setDate(QDate::currentDate());
    SetupClock();
    ui->chkBastard->setToolTip("Only stop alarms after a random math problem has been solved.");
    ui->chkSounds->setToolTip("Use a custom sound/video file to wake up to");

    SetupSlots(QAquit,QAshow);
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

void MainWindow::ToggleWindow(QSystemTrayIcon::ActivationReason Reason)
{
    if(Reason==QSystemTrayIcon::DoubleClick || Reason==QSystemTrayIcon::Trigger)
    {
        ToggleWindow();
    }
}

void MainWindow::ToggleWindow()
{
    if(this->CurAlarm->isPlaying() && this->CurAlarm->isBastard==false)
    {
        this->CurAlarm->Stop();
    }
    ui->TestBtn->setText("Test");
    if(this->isHidden())
    {
        this->show();
    }else{
        this->hide();
    }
    UpdateListWidget();
}

void MainWindow::SetTime()
{

    //If there is no selected row. Enter was probably hit, the time registered, folowed by
    //on change trigger, execpt the changes have already been logged
    if(ui->listWidget->currentIndex().column()!=-1)
    {
        if(ui->timeEdit->time().hour()>12 && !_isMilTime && _WarnOnPm)
        {
            PMWarning();
        }
        ScheduleModel *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
        Active->AlarmTime = ui->timeEdit->time();
        UpdateListWidget();
        this->_Schedules->Save();
    }
}

void MainWindow::SetCustomDate()
{
    if(ui->listWidget->currentIndex().column()!=-1)
    {
        //Update date on the display
        ui->CustEdit->setDate(ui->calendarWidget->selectedDate());
        ScheduleModel *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
        Active->AlarmTime = ui->timeEdit->time();
        QDate CustomDate=ui->calendarWidget->selectedDate();
        Active->CustomAlarm = CustomDate;
        if(Active->isCustomAlarmEnabled)
            UpdateListWidget();
        this->_Schedules->Save();
    }
}

void MainWindow::ToggleBastard(bool val)
{
    ScheduleModel *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->isBastard = val;
    UpdateListWidget();
    this->_Schedules->Save();
    SendTrayMessage(solveNotificationTitle,solveNotification);
}

void MainWindow::ToggleMon(bool isEnabled)
{
    ScheduleModel *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->isMonEnabled = isEnabled;
    UpdateListWidget();
}

void MainWindow::ToggleTue(bool isEnabled)
{
    ScheduleModel *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->isTueEnabled = isEnabled;
    UpdateListWidget();
}
void MainWindow::ToggleWed(bool isEnabled)
{
    ScheduleModel *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->isWedEnabled = isEnabled;
    UpdateListWidget();
}
void MainWindow::ToggleThur(bool isEnabled)
{
    ScheduleModel *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->isThurEnabled = isEnabled;
    UpdateListWidget();
}
void MainWindow::ToggleFri(bool isEnabled)
{
    ScheduleModel *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->isFriEnabled = isEnabled;
    UpdateListWidget();
}
void MainWindow::ToggleSat(bool isEnabled)
{
    ScheduleModel *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->isSatEnabled = isEnabled;
    UpdateListWidget();
}
void MainWindow::ToggleSun(bool isEnabled)
{
    ScheduleModel *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->isSunEnabled = isEnabled;
    UpdateListWidget();
}


void MainWindow::ToggleCust(bool isEnabled)
{
    ScheduleModel *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->isCustomAlarmEnabled = isEnabled;
    UpdateListWidget();
}

void MainWindow::ToggleOneshot(bool isEnabled)
{
    ScheduleModel *Active = this->_Schedules->GetSchedule(this->ui->listWidget->currentRow());
    Active->isOneshot = isEnabled;
    UpdateListWidget();
    if(isEnabled)
    {
        DisableGUIIfOneshot(true);
    }else{
        DisableGUIIfOneshot(false);
    }
}

void MainWindow::Quit()
{
    if(this->CurAlarm->isPlaying() && this->CurAlarm->isBastard)
    {
        //message box will cause app to exit even though we told it not too. wtf
        //QMessageBox::warning(this,"Nope","you didn't think it was going to be that easy did you?");
        return;
    }else{
        this->_Schedules->Save();
        FileIO::DelExtracted();
        FileIO::SaveVolume(ui->VolumeSlider->value());
        qApp->quit();
    }
}

void MainWindow::AddRemoveAlarm(QAbstractButton *button)
{
    if(button->text()=="&Add")
    {
        ScheduleModel *scheToAdd=new ScheduleModel(this);
        this->_Schedules->AddSchedule(scheToAdd);
        ui->listWidget->addItem(scheToAdd->Name());
        int listIndex = ui->listWidget->count()-1;
        scheToAdd->Index = listIndex;
        ui->listWidget->setCurrentRow(listIndex);
    }
    else if(button->text()=="&Remove")
    {
        this->_lastDeletedIndex=ui->listWidget->currentRow();
        this->_Schedules->removeScheduleByIndex(ui->listWidget->currentRow());
        PopulateListWidget();
    }
    else if(button->text()=="Clone")
    {
        ScheduleModel *toClone = this->_Schedules->GetSchedule(ui->listWidget->currentRow());
        ScheduleModel *cloned = new ScheduleModel(this);
        cloned->CustomAlarm = toClone->CustomAlarm;
        cloned->isCustomAlarmEnabled = toClone->isCustomAlarmEnabled;
        cloned->isCustomSoundEnabled = toClone->isCustomSoundEnabled;
        cloned->isFriEnabled = toClone->isFriEnabled;
        cloned->isMonEnabled = toClone->isMonEnabled;
        cloned->isSatEnabled = toClone->isSatEnabled;
        cloned->isSunEnabled = toClone->isSunEnabled;
        cloned->isThurEnabled = toClone->isThurEnabled;
        cloned->isTueEnabled = toClone->isTueEnabled;
        cloned->isWedEnabled = toClone->isWedEnabled;
        cloned->isBastard = toClone->isBastard;
        cloned->AlarmTime = toClone->AlarmTime;
        cloned->CustomSoundPath = toClone->CustomSoundPath;
        this->_Schedules->AddSchedule(cloned);
        PopulateListWidget();
    }
    this->_Schedules->Save();
}



void MainWindow::ShowActiveAlarm(int index)
{
    if(!ui->listAlmBtn->button(QDialogButtonBox::Cancel)->isEnabled())
        ui->listAlmBtn->button(QDialogButtonBox::Cancel)->setDisabled(false);
    DisablePanelIfNoSelection();
    if(index==-1)
    {
        //in the middle of a list clear. Running further will cause seg fault
        this->ui->listAlmBtn->button(QDialogButtonBox::Ignore)->setDisabled(true);//clone button
        return;
    }
    this->ui->listAlmBtn->button(QDialogButtonBox::Ignore)->setDisabled(false);
    ScheduleModel *active=this->_Schedules->GetSchedule(index);
    ui->timeEdit->setTime(active->AlarmTime);

    ui->chkCustom->setChecked(active->isCustomAlarmEnabled);
    ui->CustEdit->setDate(active->CustomAlarm);
    ui->chkSounds->setChecked(active->isCustomSoundEnabled);
    ui->txtSoundPath->setText(active->CustomSoundPath);

    ui->chkMon->setChecked(active->isMonEnabled);
    ui->chkTues->setChecked(active->isTueEnabled);
    ui->chkWed->setChecked(active->isWedEnabled);
    ui->chkThurs->setChecked(active->isThurEnabled);
    ui->chkFri->setChecked(active->isFriEnabled);
    ui->chkSat->setChecked(active->isSatEnabled);
    ui->chkSun->setChecked(active->isSunEnabled);
    ui->calendarWidget->setSelectedDate(active->CustomAlarm);
    ui->chkBastard->setChecked(active->isBastard);

    if(active->isOneshot)
    {
        DisableGUIIfOneshot(true);
    }
}

void MainWindow::DisableGUIIfOneshot(bool value)
{
    ui->chkFri->setDisabled(value);
    ui->chkThurs->setDisabled(value);
    ui->chkWed->setDisabled(value);
    ui->chkTues->setDisabled(value);
    ui->chkMon->setDisabled(value);
    ui->chkSun->setDisabled(value);
    ui->chkSat->setDisabled(value);
}

void MainWindow::timeCheck()
{
    UpdateClock();
    SnoozeMenuCheck();
    BastardMenuCheck();
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
    ScheduleModel *Active=this->_Schedules->GetSchedule(ui->listWidget->currentRow());
    Active->isCustomSoundEnabled = isChecked;
    if(isChecked)
    {
        QString AlarmLocation = QFileDialog::getOpenFileName(this,"Select Alarm File",QDir::homePath());
        Active->CustomSoundPath = AlarmLocation;
        ui->txtSoundPath->setText(AlarmLocation);
    }else{
        ui->txtSoundPath->setText("");
    }
    this->_Schedules->Save();
}

void MainWindow::TestAlarm()
{
    if(ui->chkSounds->isChecked())
    {
        this->CurAlarm->SetCustomPath(ui->txtSoundPath->text());
        this->CurAlarm->Start(true);
    }else{
        this->CurAlarm->Start(false);
    }
    CurAlarm->isBastard=this->ui->chkBastard->isChecked();
    this->testrun=true;
}

void MainWindow::ShowAbout()
{
    AboutDialog *aboutbox=new AboutDialog(this);
    aboutbox->show();
}


void MainWindow::SnoozeMenuCheck()
{
    if((this->testrun==true && this->CurAlarm->isBastard==false) || (this->CurAlarm->isPlaying() && this->CurAlarm->canResume && this->CurAlarm->isBastard==false))
    {
        //Create Snooze Menu object
        snooze *snMenu=new snooze(this,CurAlarm, this->_Schedules);
        snMenu->show();
        if(this->_supportsTray && this->testrun==false)
        {
            this->hide();
        }
        this->CurAlarm->canResume=false;
        this->testrun=false;
    }
}

void MainWindow::BastardMenuCheck()
{
    if((this->testrun==true && this->CurAlarm->isBastard==true) || (this->CurAlarm->isPlaying() && this->CurAlarm->canResume &&  this->CurAlarm->isBastard))
    {
        BastardSnooze *bsnooze= new BastardSnooze(this,this->CurAlarm, this->_Schedules);
        bsnooze->show();
        if(this->_supportsTray && this->testrun==false)
        {
            this->hide();
        }
        this->CurAlarm->canResume=false;
        this->testrun=false;
    }
}

void MainWindow::PMWarning()
{
    QMessageBox::warning(this,"Time Verification","Your selected time is set for PM. If you intended to wake in the morning, now is your chance to fix it");
}


void MainWindow::ShowSettings()
{
    SettingDialog *settingsPage=new SettingDialog(this,&_isMilTime, &_WarnOnPm, trayIcon);
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
    ScheduleModel *sche;
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
        ui->chkBastard->setEnabled(false);
        ui->lblTime->setEnabled(false);

        ui->chkCustom->setChecked(false);
        ui->chkFri->setChecked(false);
        ui->chkMon->setChecked(false);
        ui->chkBastard->setChecked(false);
        ui->chkSat->setChecked(false);
        ui->chkSounds->setChecked(false);
        ui->chkSun->setChecked(false);
        ui->chkThurs->setChecked(false);
        ui->chkTues->setChecked(false);
        ui->chkWed->setChecked(false);
        ui->txtSoundPath->setText("");
        ui->chkOnshot->setEnabled(false);

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
        ui->chkBastard->setEnabled(true);
        ui->lblTime->setEnabled(true);
        ui->chkOnshot->setEnabled(true);
    }
}

void MainWindow::UpdateListWidget()
{
    int index=ui->listWidget->currentRow();
    PopulateListWidget();
    ui->listWidget->setCurrentRow(index);
    this->_Schedules->Save();
}

void MainWindow::SendTrayMessage(QString title, QString message)
{
    if(!FileIO::LoadSeenSolveText())
    {
        QIcon icon;
        if(FileIO::LoadisMono())
        {
            icon = QIcon(":/new/icons/mono.png");
        }else{
            icon = QIcon(":/new/icons/Clock.png");
        }
        trayIcon->showMessage(title,message,icon);
        FileIO::SaveSeenSolveText();
    }
}

void MainWindow::ChangeIconToDefault()
{
    trayIcon->setToolTip("QTalarm");
    if(FileIO::LoadisMono())
    {
        this->trayIcon->setIcon(QIcon(":/new/icons/mono.png"));
    }else{
        this->trayIcon->setIcon(QIcon(":/new/icons/Clock.png"));
    }
}


void MainWindow::SetupSlots(QAction *QAquit, QAction *QAshow)
{
    //set up ui slots
    connect(QAquit,SIGNAL(triggered()),this,SLOT(Quit()));
    connect(QAshow,SIGNAL(triggered()),this,SLOT(ToggleWindow()));
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(ToggleWindow(QSystemTrayIcon::ActivationReason)));
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
    connect(ui->chkBastard,SIGNAL(clicked(bool)),this,SLOT(ToggleBastard(bool)));
    connect(ui->TestBtn,SIGNAL(clicked()),this,SLOT(TestAlarm()));
    connect(ui->VolumeSlider,SIGNAL(valueChanged(int)),CurAlarm,SLOT(SetVolume(int)));
    connect(ui->calendarWidget,SIGNAL(clicked(QDate)),this,SLOT(SetCustomDate()));
    connect(ui->chkOnshot,SIGNAL(clicked(bool)),this,SLOT(ToggleOneshot(bool)));

}

void MainWindow::SetupTrayIcon(QAction *QAshow, QAction *QAquit)
{
    trayIcon=new QSystemTrayIcon(this);
    trayIconMenu=new QMenu(this);

    trayIconMenu->addAction(QAshow);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(QAquit);
    trayIcon->setContextMenu(trayIconMenu);
    ChangeIconToDefault();
    trayIcon->show();

}

void MainWindow::SetupVolume()
{
    int Volume = FileIO::LoadVolume();
    ui->VolumeSlider->setValue(Volume<=0? 50:Volume);
    CurAlarm->SetVolume(ui->VolumeSlider->value());
}

void MainWindow::ConfigureButtons()
{
    this->ui->listAlmBtn->button(QDialogButtonBox::Ignore)->setText("Clone");
    this->ui->listAlmBtn->button(QDialogButtonBox::Ignore)->setDisabled(true);
    ui->listAlmBtn->button(QDialogButtonBox::Ok)->setText("&Add");
    ui->listAlmBtn->button(QDialogButtonBox::Cancel)->setText("&Remove");
    ui->listAlmBtn->button(QDialogButtonBox::Cancel)->setDisabled(true);
}

void MainWindow::LoadOptions()
{
    _isMilTime=FileIO::isMilTime();
    _WarnOnPm=FileIO::LoadWarnOnPm();
    _prevTimeWasMil=_isMilTime;
    displayTimeMode();
}

void MainWindow::TerminateIfRunning()
{
    const QString appKey = "qtalarmLocal";

    QLocalSocket *socket = new QLocalSocket(this);
    socket->connectToServer(appKey);

    QLocalSocket::LocalSocketState status = socket->state();
    if (status == QLocalSocket::ConnectedState)
    {
        socket->close();
        socket->deleteLater();
        qInfo() << "Application already running. Exiting";
        exit(EXIT_FAILURE);
    }
    socket->deleteLater();


    //used for process communication for duplicate processes
    QLocalServer *m_server = new QLocalServer(this);
    connect(m_server, SIGNAL(newConnection()), this, SLOT(handleLocalConnection()));
    m_server->setSocketOptions(QLocalServer::UserAccessOption);

    if (!m_server->listen(appKey))
    {
        qInfo() << "Unable to start Local Process Server";
    } else {
        qInfo() << "Local-only Process Server up and running";
    }
}

void MainWindow::handleLocalConnection()
{
    if(toggleOnDuplicateProcess)
    {
        ToggleWindow();
    }else{
        this->show();
    }
}
