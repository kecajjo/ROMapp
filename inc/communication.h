#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "datafordatatable.h"
#include <QtBluetooth/QBluetoothDeviceInfo>
#include <thread>
#include <mutex>

class Communication{
    DataForDataTable Data;
    bool NewData;
    mutable std::mutex DataMutex;

    QList<QBluetoothDeviceInfo> *Devices;
    QBluetoothDeviceInfo *DeviceToConnect;
    bool ConnectCommand;
    bool BluetoothConnected;
    bool ConnectionError;
    bool BluetoothDisconnect;
    bool ScanCommand;
    bool ScanComplete;
    bool DevLstChanged;
    mutable std::mutex BluetoothMutex;

public:
    Communication();
    ~Communication();

    /*
     * Data operations
    */
    void SendData(DataForDataTable DataToSend);
    DataForDataTable ReadData();

    /*
     * Information set by GUI
    */
    void ConnectToDeviceCommand(int LstIdx);
    void ScanForDevicesCommand();
    void DisconnectCommand(){BluetoothDisconnect = true; ConnectionError=false;}
    void ClearDevLstChanged(){DevLstChanged = false;}

    /*
     * Information received by GUI
    */
    bool IsNewData() const {return NewData;}
    bool IsScanComplete() const {return ScanComplete;}
    bool IsConnectionError() const {return ConnectionError;}
    bool IsBluetoothConnected() const {return BluetoothConnected;}
    bool IsDevLstChanged() const {return DevLstChanged;}
    QList<QBluetoothDeviceInfo>* GetDevices() const {return Devices;}

    /*
     * Information set by logic
    */
    void NewDevLst(QList<QBluetoothDeviceInfo>* Lst){Devices = Lst;}
    void NewDevice(){DevLstChanged = true;}
    void ScanFinished(QList<QBluetoothDeviceInfo> *DevLst);
    void Disconnected(){BluetoothConnected = false; BluetoothDisconnect = false;}
    void Connected(){ConnectionError = false; BluetoothConnected = true;}
    void ConnectionFailed(){ConnectionError = true;}
    void ClearScanCommand(){ScanCommand = false; ScanComplete = false;}
    void ClearDisconnectCommand(){BluetoothDisconnect = false;}

    /*
     * Information received by Logic
    */
    bool IsScanCommand() const {return ScanCommand;}
    bool IsDisconnectCommand() const {return BluetoothDisconnect;}
    bool IsConnectCommand() const {return ConnectCommand;}
    QBluetoothDeviceInfo* DeviceToConnectTo();

    void ClearConnectionError(){ConnectionError = false;}
};

#endif // COMMUNICATION_H
