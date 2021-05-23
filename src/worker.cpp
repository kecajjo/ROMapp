#include "worker.h"
#include "unistd.h"
#include <QDebug>

Worker::Worker(QObject *parent) : QObject(parent){
    Comm = nullptr;
    ConvertedData = nullptr;
    BT = nullptr;
    connect(this, &Worker::StartSig, this, &Worker::Start);
}

Worker::~Worker(){
    if(Tim != nullptr){
        delete Tim;
    }
    if(ConvertedData != nullptr){
        delete ConvertedData;
    }
    if(BT != nullptr){
        delete BT;
    }
}

void Worker::Start(){
    Tim = new QTimer;
    connect(Tim, &QTimer::timeout, this, &Worker::CheckEvents);
    Tim->start(50);
    ConvertedData = new DataTransform;
    BT = new BTCommunication;
    connect(BT, SIGNAL(NewDevice(QBluetoothDeviceInfo)), this, SLOT(DeviceFound()));
    connect(BT, SIGNAL(ServiceConnected()), this, SLOT(Connected()));
    connect(BT, SIGNAL(ServiceDisconnected()), this, SLOT(Disconnected()));
    connect(BT, SIGNAL(ConnectionError()), this, SLOT(ConnectionError()));
    connect(BT, SIGNAL(NewDevLst(QList<QBluetoothDeviceInfo>*)), this, SLOT(NewDevLst(QList<QBluetoothDeviceInfo>*)));
    connect(BT, SIGNAL(NewMessage(QByteArray*)), this, SLOT(ReceiveMessage(QByteArray*)));
}

void Worker::CheckEvents(){
    QBluetoothDeviceInfo *DevInfo;

    //is time to end
    if(Comm->IsEndCommand()){
        if(Tim != nullptr){
            Tim->stop();
            this->thread()->exit();
        }
    }

    // Bluetooth received events
    if(Comm->IsScanCommand()){
        Comm->ClearScanCommand();
        BT->StartScan();
    }
    if(Comm->IsConnectCommand()){
        DevInfo = Comm->DeviceToConnectTo();
        if(DevInfo != nullptr){
            BT->ConnectToDevice(*DevInfo);
        }
    }
    if(Comm->IsDisconnectCommand()){
        Comm->ClearDisconnectCommand();
        BT->Disconnect();
    }
}

void Worker::ConnectionError(){
    Comm->Disconnected();
    Comm->ConnectionFailed();
}

void Worker::NewDevLst(QList<QBluetoothDeviceInfo> *Lst){
    Comm->NewDevLst(Lst);
}

void Worker::ReceiveMessage(QByteArray *RawData){
    ConvertedData->CalculateData(RawData);
    Comm->SendData(ConvertedData->GetData());
}
