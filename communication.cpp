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
    //ignore command if devices list is empty or devices==nullptr
    if(Devices == nullptr) return;
    if(Devices->isEmpty()) return;
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

QBluetoothDeviceInfo* Communication::DeviceToConnectTo(){
    if(ConnectCommand == true){
        std::lock_guard<std::mutex> Grd(BluetoothMutex);
        ConnectCommand = false;
        return DeviceToConnect;
    }
    return nullptr;
}
