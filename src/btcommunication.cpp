#include "btcommunication.h"

BTCommunication::BTCommunication(QObject *parent)
    : QObject(parent){

    DiscoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    LocDev = new QBluetoothLocalDevice;
    Socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    Devices = new QList<QBluetoothDeviceInfo>;

    connect(Socket, SIGNAL(disconnected()), this, SIGNAL(ServiceDisconnected()));
    connect(DiscoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(AddDeviceToList(QBluetoothDeviceInfo)));
    connect(DiscoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SIGNAL(NewDevice(QBluetoothDeviceInfo)));
    connect(DiscoveryAgent, SIGNAL(finished()), this, SLOT(ScanEnded()));
    connect(Socket, SIGNAL(connected()), this, SIGNAL(ServiceConnected()));
    connect(Socket, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(DiscoveryAgent, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)), this, SLOT(DiscoveryError(QBluetoothDeviceDiscoveryAgent::Error)));
    connect(Socket, SIGNAL(error(QBluetoothSocket::SocketError)), this, SIGNAL(ConnectionError()));
    Socket->close();
}

BTCommunication::~BTCommunication(){
    delete LocDev;
    delete DiscoveryAgent;
    delete Socket;
    delete Devices;
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
    Socket->connectToService(QBluetoothAddress(ConnectedDeviceAddress), QBluetoothUuid(QBluetoothUuid::SerialPort), QIODevice::ReadWrite);
}

void BTCommunication::ScanEnded(){
    emit ScanFinished(Devices);
}

void BTCommunication::ReadData(){
    char Data[50];
    Socket->readLine(Data,50);
}

void BTCommunication::DiscoveryError(QBluetoothDeviceDiscoveryAgent::Error Err){
}
