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
    Tim->start(1000);
    ConvertedData = new DataTransform;
    BT = new BTCommunication;
}
void Worker::CheckEvents(){
    DataFromSTM Test;
    QBluetoothDeviceInfo *DevInfo;
    bool NewDataFromBT = true;
    ConvertedData->ReadExampleData();
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
