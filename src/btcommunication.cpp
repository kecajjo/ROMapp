#include "btcommunication.h"

BTCommunication::BTCommunication(QObject *parent)
    : QObject(parent){

    DiscoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    LocDev = new QBluetoothLocalDevice;
    Socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    Devices = new QList<QBluetoothDeviceInfo>;
    Message = new QByteArray;
    StoredData = new QByteArray;

    connect(Socket, SIGNAL(disconnected()), this, SIGNAL(ServiceDisconnected()));
    connect(DiscoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(AddDeviceToList(QBluetoothDeviceInfo)));
    connect(DiscoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SIGNAL(NewDevice(QBluetoothDeviceInfo)));
    connect(DiscoveryAgent, SIGNAL(finished()), this, SLOT(ScanEnded()));
    connect(Socket, SIGNAL(connected()), this, SIGNAL(ServiceConnected()));
    connect(Socket, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(Socket, SIGNAL(error(QBluetoothSocket::SocketError)), this, SIGNAL(ConnectionError()));
    Socket->close();
}

BTCommunication::~BTCommunication(){
    delete LocDev;
    delete DiscoveryAgent;
    delete Socket;
    delete Devices;
    delete Message;
    delete StoredData;
}

void BTCommunication::StartScan(){
    Devices->clear();
    emit NewDevLst(Devices);
    DiscoveryAgent->setInquiryType(QBluetoothDeviceDiscoveryAgent::GeneralUnlimitedInquiry);
    DiscoveryAgent->start();
}

void BTCommunication::AddDeviceToList(const QBluetoothDeviceInfo &NewDev){
    Devices->append(NewDev);
}

void BTCommunication::ConnectToDevice(const QBluetoothDeviceInfo &Device){
    Socket->disconnectFromService();
    ConnectedDeviceAddress = Device.address().toString();
    //Socket->connectToService(QBluetoothAddress(ConnectedDeviceAddress), QBluetoothUuid(QString("00001101-0000-1000-8000-00805F9B34FB")), QIODevice::ReadWrite);
    Socket->connectToService(QBluetoothAddress(ConnectedDeviceAddress), QBluetoothUuid(QBluetoothUuid::SerialPort), QIODevice::ReadWrite);
}

void BTCommunication::ScanEnded(){
    emit ScanFinished(Devices);
}

void BTCommunication::ReadData(){
    *StoredData += Socket->read(FRAME_LEN);
    int StartIdx = StoredData->indexOf(OPTION_DATA);
    if(StartIdx == -1) return;
    if(StoredData->length() >= StartIdx + FRAME_LEN){ //if full message is ready
        Message->clear();
        QByteArray::iterator Iter = StoredData->begin();
        Iter+=StartIdx;
        for(int i=0;i<FRAME_LEN-1;i++){
            Iter++; //starting to append from 1st data byte (skipping addr byte)
            Message->append(*Iter);
        }
        emit NewMessage(Message);
        StoredData->remove(0,StartIdx+FRAME_LEN);
    }
}
