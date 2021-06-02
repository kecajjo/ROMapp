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
    /*!
     * \brief Data
     * Data sent from robot
     */
    DataForDataTable Data;
    /*!
     * \brief NewData
     * Tells if data has been updated since last reading
     */
    bool NewData;
    /*!
     * \brief DataMutex
     * Doesn't allow data to be accessed at the same time by different threads
     */
    mutable std::mutex DataMutex;

    /*!
     * \brief Devices
     * List of bluetooth devices that were found while scan
     */
    QList<QBluetoothDeviceInfo> *Devices;
    /*!
     * \brief DeviceToConnect
     * Stores information about device which is to be connected
     */
    QBluetoothDeviceInfo *DeviceToConnect;
    /*!
     * \brief ConnectCommand
     * True if GUI sent command to connect to bluetooth device stored under DeviceToConnect
     * false otherwise
     */
    bool ConnectCommand;
    /*!
     * \brief BluetoothConnected
     * True if device is connected
     * False otherwise
     */
    bool BluetoothConnected;
    /*!
     * \brief ConnectionError
     * True if error occured while connecting to bluetooth
     * False otherwise
     */
    bool ConnectionError;
    /*!
     * \brief BluetoothDisconnect
     * True if GUI sent command to disconnect from bluetooth device
     * false otherwise
     */
    bool BluetoothDisconnect;
    /*!
     * \brief ScanCommand
     * True if GUI sent command to scan for bluetooth devices
     * False otherwise
     */
    bool ScanCommand;
    /*!
     * \brief ScanComplete
     * True if scan for bluetooth devices has finished
     * False otherwise
     */
    bool ScanComplete;
    /*!
     * \brief DevLstChanged
     * True if list Devices has changed
     * False otherwise
     */
    bool DevLstChanged;
    /*!
     * \brief BluetoothMutex
     * Doesn't allow bluetooth information to be accessed at the same time by different threads
     */
    mutable std::mutex BluetoothMutex;

    /*!
     * \brief EndCommand
     * Command for worker thread to finish
     */
    bool EndCommand;

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

    /*!
     * \brief End
     * Sets EndCommand to true
     */
    void End(){EndCommand = true;}
    /*!
     * \brief IsEndCommand
     * \return true if EndCommand is set, false otherwise
     * Allows to check if end command was sent
     */
    bool IsEndCommand() const {return EndCommand;}
};

#endif // COMMUNICATION_H
