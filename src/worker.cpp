#include "worker.h"
#include "unistd.h"

Worker::Worker(QObject *parent) : QObject(parent){
    Comm = nullptr;
    ConvertedData = nullptr;
    BT = nullptr;
    connect(this, &Worker::StartSig, this, &Worker::Start);
}

Worker::~Worker(){
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
    Tim->start(100);
    ConvertedData = new DataTransform;
    BT = new BTCommunication;
    connect(BT, SIGNAL(NewDevice(QBluetoothDeviceInfo)), this, SLOT(DeviceFound()));
    connect(BT, SIGNAL(ServiceConnected()), this, SLOT(Connected()));
    connect(BT, SIGNAL(ServiceConnected()), this, SLOT(Disconnected()));
    connect(BT, SIGNAL(ConnectionError()), this, SLOT(ConnectionError()));
    connect(BT, SIGNAL(NewDevLst(QList<QBluetoothDeviceInfo>*)), this, SLOT(NewDevLst(QList<QBluetoothDeviceInfo>*)));
}

void Worker::CheckEvents(){
    DataFromSTM Test;
    QBluetoothDeviceInfo *DevInfo;
    bool NewDataFromBT = true;
    ConvertedData->ReadExampleData();

    // Bluetooth received events
    if(NewDataFromBT == true){
        ConvertedData->CalculateData(Test);
        Comm->SendData(ConvertedData->GetData());
    }
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

void Worker::NewDevLst(QList<QBluetoothDeviceInfo>* Lst){
    Comm->NewDevLst(Lst);
}
