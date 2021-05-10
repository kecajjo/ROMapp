#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "datafordatatable.h"
#include <QtBluetooth/QBluetoothDeviceInfo>
#include <thread>
#include <mutex>

/*!
 * \brief The Communication class
 * allows communication between worker thread and main thread
 */
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
    /*!
     * \brief Communication
     * Default class constructor
     */
    Communication();
    ~Communication();

    /*
     * Data operations
    */
    /*!
     * \brief SendData
     * \param[in] DataToSend - data which will be sent
     */
    void SendData(DataForDataTable DataToSend);
    /*!
     * \brief ReadData
     * \return Stored data
     */
    DataForDataTable ReadData();

    /*
     * Information set by GUI
    */
    /*!
     * \brief ConnectToDeviceCommand
     * \param[in] LstIdx - list index of device to connect to
     * Sets command to connect to device, sets which device to connect to
     */
    void ConnectToDeviceCommand(int LstIdx);
    /*!
     * \brief ScanForDevicesCommand
     * Sets scan command
     */
    void ScanForDevicesCommand();
    /*!
     * \brief DisconnectCommand
     * Sets disconnect command
     */
    void DisconnectCommand(){BluetoothDisconnect = true; ConnectionError=false;}
    /*!
     * \brief ClearDevLstChanged
     * Changes devices list status from changed to unchanged
     */
    void ClearDevLstChanged(){DevLstChanged = false;}

    /*
     * Information received by GUI
    */
    /*!
     * \brief IsNewData
     * \return true if there is new data available, false otherwise
     */
    bool IsNewData() const {return NewData;}
    /*!
     * \brief IsScanComplete
     * \return true is scan was complete, false otherwise
     */
    bool IsScanComplete() const {return ScanComplete;}
    /*!
     * \brief IsConnectionError
     * \return true if there was connection error, false otherwise
     */
    bool IsConnectionError() const {return ConnectionError;}
    /*!
     * \brief IsBluetoothConnected
     * \return true if bluetooth is connected to device, false otherwise
     */
    bool IsBluetoothConnected() const {return BluetoothConnected;}
    /*!
     * \brief IsDevLstChanged
     * \return true if devices list was changed, false otherwise
     */
    bool IsDevLstChanged() const {return DevLstChanged;}
    /*!
     * \brief GetDevices
     * \return list of found bluetooth devices
     */
    QList<QBluetoothDeviceInfo>* GetDevices() const {return Devices;}

    /*
     * Information set by logic
    */
    /*!
     * \brief NewDevLst
     * \param[in] Lst - list to be assigned to devices list
     * Assigns devices list to Lst
     */
    void NewDevLst(QList<QBluetoothDeviceInfo>* Lst){Devices = Lst;}
    /*!
     * \brief NewDevice
     * Changes devices list status from unchanged to changed
     */
    void NewDevice(){DevLstChanged = true;}
    /*!
     * \brief ScanFinished
     * \param[in] DevLst - list containing found devices
     * Assigns devices list to DevLst and changes status of flags;
     */
    void ScanFinished(QList<QBluetoothDeviceInfo> *DevLst);
    /*!
     * \brief Disconnected
     * Changes flags status to disconected
     */
    void Disconnected(){BluetoothConnected = false; BluetoothDisconnect = false;}
    /*!
     * \brief Connected
     * Changes flags status to connected
     */
    void Connected(){ConnectionError = false; BluetoothConnected = true;}
    /*!
     * \brief ConnectionFailed
     * Sets connection failed flag
     */
    void ConnectionFailed(){ConnectionError = true;}
    /*!
     * \brief ClearScanCommand
     * Resets scan command
     */
    void ClearScanCommand(){ScanCommand = false; ScanComplete = false;}
    /*!
     * \brief ClearDisconnectCommand
     * Resets disconnect command
     */
    void ClearDisconnectCommand(){BluetoothDisconnect = false;}

    /*
     * Information received by Logic
    */
    /*!
     * \brief IsScanCommand
     * \return true if scan command is set, false otherwise
     */
    bool IsScanCommand() const {return ScanCommand;}
    /*!
     * \brief IsDisconnectCommand
     * \return  true if disconnect command is set, false otherwise
     */
    bool IsDisconnectCommand() const {return BluetoothDisconnect;}
    /*!
     * \brief IsConnectCommand
     * \return true if connect command is set, false otherwise
     */
    bool IsConnectCommand() const {return ConnectCommand;}
    /*!
     * \brief DeviceToConnectTo
     * \return information which device to connect to, nullptr if no device is set
     */
    QBluetoothDeviceInfo* DeviceToConnectTo();


    /*!
     * \brief ClearConnectionError
     * Resets connection error flag
     */
    void ClearConnectionError(){ConnectionError = false;}
};

#endif // COMMUNICATION_H
