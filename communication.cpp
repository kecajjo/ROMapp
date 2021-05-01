#include "communication.h"

Communication::Communication(){
    NewData = false;
    ConnectCommand = false;
    BluetoothDisconnect = false;
    BluetoothConnected = false;
    ScanCommand = false;
    ScanComplete = false;
    ExitCommand = false;
    ConnectionError = false;
    Devices = nullptr;
    DeviceToConnect = nullptr;
}

Communication::~Communication(){
}

void Communication::SendData(DataForDataTable DataToSend){
    std::lock_guard<std::mutex> Grd(DataMutex);
    Data = DataToSend;
    NewData = true;
}

DataForDataTable Communication::ReadData(){
    std::lock_guard<std::mutex> Grd(DataMutex);
    NewData = false;
    return Data;
}

void Communication::ConnectToDeviceCommand(int LstIdx){
    std::lock_guard<std::mutex> Grd(BluetoothMutex);
    *DeviceToConnect = Devices->at(LstIdx);
    ConnectionError = false;
    ConnectCommand = true;
}

void Communication::ScanForDevicesCommand(){
    std::lock_guard<std::mutex> Grd(BluetoothMutex);
    ScanComplete = false;
    Devices = nullptr;
    ScanCommand = true;
}

void Communication::ScanFinished(QList<QBluetoothDeviceInfo> const &DevLst){
    std::lock_guard<std::mutex> Grd(BluetoothMutex);
    ScanComplete = true;
    *Devices = DevLst;
}

QBluetoothDeviceInfo* Communication::IsConnectCommand(){
    if(ConnectCommand == true){
        std::lock_guard<std::mutex> Grd(BluetoothMutex);
        ConnectCommand = false;
        return DeviceToConnect;
    }
    return nullptr;
}
