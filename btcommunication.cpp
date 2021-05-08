#include "btcommunication.h"

BTCommunication::BTCommunication(QObject *parent)
    : QObject(parent){

    DiscoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    LocDev = new QBluetoothLocalDevice;
    Socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    Devices = new QList<QBluetoothDeviceInfo>;

    connect(Socket, SIGNAL(disconnected()), this, SLOT(ServiceDisconnected()));
    connect(DiscoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(AddDeviceToList(QBluetoothDeviceInfo)));
    connect(DiscoveryAgent, SIGNAL(finished()), this, SLOT(FinishedScan()));
    connect(Socket, SIGNAL(connected()), this, SLOT(ServiceConnected()));
    connect(Socket, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(DiscoveryAgent, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)), this, SLOT(DiscoveryError(QBluetoothDeviceDiscoveryAgent::Error)));
    Socket->close();
    DiscoveryAgent->start();
}

BTCommunication::~BTCommunication(){
    delete LocDev;
    delete DiscoveryAgent;
    delete Socket;
    delete Devices;
}

void BTCommunication::StartScan(){
    qDebug() << "Scanning\n";
    Devices->clear();
    DiscoveryAgent->setInquiryType(QBluetoothDeviceDiscoveryAgent::GeneralUnlimitedInquiry);
    DiscoveryAgent->start();
}

void BTCommunication::AddDeviceToList(const QBluetoothDeviceInfo &NewDevice){
    qDebug() << "Device found: " << NewDevice.name();
    Devices->append(NewDevice);
}

void BTCommunication::ConnectToDevice(const QBluetoothDeviceInfo &Device){
    Socket->disconnectFromService();
    qDebug() << "Connecting to device " << Device.name() << " adress: " << Device.address();
    ConnectedDeviceAddress = Device.address().toString();
    Socket->connectToService(QBluetoothAddress(ConnectedDeviceAddress), QBluetoothUuid(QBluetoothUuid::SerialPort), QIODevice::ReadWrite);
}

void BTCommunication::FinishedScan(){
    qDebug() << "Scan finished";
    for(int i=0;i<Devices->length();i++){
        qDebug() << "Device " << i <<" name: " << Devices->at(i).name() << " adress: " << Devices->at(i).address();
    }
}

void BTCommunication::ServiceConnected(){
    qDebug() << "Connected";
}
void BTCommunication::ServiceDisconnected(){
    qDebug() << "Disconnected";
}

void BTCommunication::ReadData(){
    char Data[50];
    Socket->readLine(Data,50);
    qDebug() << Data;
}

void BTCommunication::DiscoveryError(QBluetoothDeviceDiscoveryAgent::Error Err){
    qDebug() << Err;
}
