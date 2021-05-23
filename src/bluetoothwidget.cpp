#include "bluetoothwidget.h"
#include "ui_bluetoothwidget.h"

BluetoothWidget::BluetoothWidget(QWidget *parent) :
    QWidget(parent),
    Ui(new Ui::BluetoothWidget){
    Ui->setupUi(this);
    Ui->LoadingGif->hide();
    Loading = new QMovie(QDir().absoluteFilePath("../ROMapp/fig/loading.gif"));
    Ui->LoadingGif->setMovie(Loading);
    InitDevBox();
    this->setWindowTitle("Bluetooth Manager");
    this->setFixedSize(533,76);

    TimDevBox = new QTimer;
    TimConnectionCheck = new QTimer;
    TimConnectionTimeout = new QTimer;

    connect(TimConnectionCheck, &QTimer::timeout, this, &BluetoothWidget::ConnectionCheck);
    connect(TimConnectionTimeout, &QTimer::timeout, this, &BluetoothWidget::ConnectionTimeout);
    connect(TimDevBox, &QTimer::timeout, this, &BluetoothWidget::RefreshDevBox);
    connect(Ui->ScanButton, &QAbstractButton::clicked, this, &BluetoothWidget::ScanButtonClicked);
    connect(Ui->ConnectButton, &QAbstractButton::clicked, this, &BluetoothWidget::ConnectButtonClicked);
    connect(Ui->DisconnectButton, &QAbstractButton::clicked, this, &BluetoothWidget::DisconnectButtonClicked);

    TimDevBox->start(1000);//Timer event every 1sec
}

BluetoothWidget::~BluetoothWidget(){
    delete TimDevBox;
    delete TimConnectionCheck;
    delete TimConnectionTimeout;
    delete Loading;
    delete Ui;
}

void BluetoothWidget::Init(Communication *ThreadComm){
        this->ThreadComm = ThreadComm;
}

void BluetoothWidget::ScanButtonClicked(){
    ThreadComm->ScanForDevicesCommand();
    Ui->LoadingGif->hide();
    Loading->stop();
}

void BluetoothWidget::ConnectButtonClicked(){
    int Idx = Ui->DevicesBox->currentIndex();
    ThreadComm->ConnectToDeviceCommand(Idx);

    Ui->LoadingGif->show();
    Loading->start();
    TimConnectionCheck->start(50);
    TimConnectionTimeout->setSingleShot(true);
    TimConnectionTimeout->start(5000);
}

void BluetoothWidget::DisconnectButtonClicked(){
    ThreadComm->DisconnectCommand();
    close();
}

void BluetoothWidget::RefreshDevBox(){
    if(ThreadComm->IsDevLstChanged()){
        ThreadComm->ClearDevLstChanged();
        QList<QString> DevBox;
        Ui->DevicesBox->clear();
        QList<QBluetoothDeviceInfo> *DevInf = ThreadComm->GetDevices();
        if(DevInf != nullptr){
            if(DevInf->length() != 0){
                QList<QBluetoothDeviceInfo>::iterator Iter;
                for(Iter=DevInf->begin(); Iter!=DevInf->end(); Iter++){
                    DevBox.append(QString(Iter->name()));
                }
                Ui->DevicesBox->addItems(DevBox);
            }
        }
    }
}

void BluetoothWidget::closeEvent(QCloseEvent *Event){
    emit AboutToClose();
    Event->accept();
}

void BluetoothWidget::ConnectionTimeout(){
    TimConnectionCheck->stop();
    Ui->LoadingGif->hide();
    Loading->stop();
    ThreadComm->DisconnectCommand();
}

void BluetoothWidget::ConnectionCheck(){
    if(ThreadComm->IsBluetoothConnected()){
        TimConnectionTimeout->stop();
        Ui->LoadingGif->hide();
        Loading->stop();
        close();
    }
}

void BluetoothWidget::InitDevBox(){
    Ui->DevicesBox->setMaxVisibleItems(5);
    Ui->DevicesBox->setInsertPolicy(QComboBox::InsertAtBottom);
}
