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
    mutable std::mutex BluetoothMutex;
    bool ExitCommand;

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

    /*
     * Information received by GUI
    */
    bool IsNewData() const {return NewData;}
    bool IsScanComplete() const {return ScanComplete;}
    bool IsConnectionError() const {return ConnectionError;}
    bool IsBluetoothConnected() const {return BluetoothConnected;}
    const QList<QBluetoothDeviceInfo>& GetDevices() const {return *Devices;}

    /*
     * Information set by logic
    */
    void ScanFinished(QList<QBluetoothDeviceInfo> const &DevLst);
    void Disconnected(){BluetoothConnected = false; BluetoothDisconnect = false;}
    void Connected(){ConnectionError = false; BluetoothConnected = true;}
    void ConnectionFailed(){ConnectionError = true;}
    void ClearScanCommand(){ScanCommand = false; ScanComplete = false;}

    /*
     * Information received by Logic
    */
    bool IsScanCommand() const {return ScanCommand;}
    bool IsDisconnectCommand() const {return BluetoothDisconnect;}
    QBluetoothDeviceInfo* IsConnectCommand();

    void ClearConnectionError(){ConnectionError = false;}
    void Exit(){ExitCommand = true;}
    bool IsExitCommand() const {return ExitCommand;}
};

#endif // COMMUNICATION_H
