#ifndef BTCOMMUNICATION_H
#define BTCOMMUNICATION_H

#include <QtBluetooth>

#define FRAME_LEN 15
#define OPTION_DATA 0xAA

/*!
 * \brief The BTCommunication class
 * class takes care of bluetooth communication between the application and external device.
 */
class BTCommunication : public QObject{
    Q_OBJECT
public:
    /*!
     * \brief BTCommunication
     * \param[in] parent - parent QObject
     * Initializes all signal-slot connections.
     */
    BTCommunication(QObject *parent = nullptr);
    ~BTCommunication();
    /*!
     * \brief StartScan
     * Scans for nearby bluetooth devices.
     *
     * Clears devices list, starts scanning for nearby devices and emits signal NewDewLst.
     */
    void StartScan();
    /*!
     * \brief ConnectToDevice
     * \param[im] Device
     * Disconnects from the current service and connects to the Device.
     */
    void ConnectToDevice(const QBluetoothDeviceInfo &Device);
    /*!
     * \brief Disconnect
     * Disconnects from the current service.
     */
    void Disconnect(){Socket->disconnectFromService();}
private slots:
    /*!
     * \brief AddDeviceToList
     * \param NewDevice[in]
     * Adds the NewDevice to the Devices list.
     */
    void AddDeviceToList(const QBluetoothDeviceInfo &NewDevice);
    /*!
     * \brief ReadData
     * Reads messages and send them with the NewMessage signal.
     *
     * Searches for byte containing the OPTION (currently OPTION_DATA is the only OPTION)
     * If full message is stored emits it and removes it from the stored data.
     */
    void ReadData();
    /*!
     * \brief ScanEnded
     * Emits ScanFinished signal.
     */
    void ScanEnded();

signals:
    /*!
     * \brief ScanFinished
     * Signal emitted once devices scan has finished, contains full list of discovered devices.
     */
    void ScanFinished(QList<QBluetoothDeviceInfo>*);
    /*!
     * \brief ServiceDisconnected
     * Signal emitted once service was disconnected from Socket.
     */
    void ServiceDisconnected();
    /*!
     * \brief ServiceConnected
     * Signal emiited when successfully connected to the service.
     */
    void ServiceConnected();
    /*!
     * \brief ConnectionError
     * Signal emitted when Socket error happens.
     */
    void ConnectionError();
    /*!
     * \brief NewDevice
     * Signal emitted when new device is found, contains information about the device.
     */
    void NewDevice(QBluetoothDeviceInfo);
    /*!
     * \brief NewDevLst
     * Signal emitted when Devices list is cleared, contains pointer to the list.
     */
    void NewDevLst(QList<QBluetoothDeviceInfo>*);
    /*!
     * \brief NewMessage
     * Signal is emitted once there is available new message in the socket, contains message.
     *
     * NOTE: if nothing reads this signal, data from message is lost.
     */
    void NewMessage(QByteArray*);

private:
    /*!
     * \brief DiscoveryAgent
     * Used to scan for devices.
     */
    QBluetoothDeviceDiscoveryAgent *DiscoveryAgent;
    /*!
     * \brief LocDev
     * Information about the local device.
     */
    QBluetoothLocalDevice *LocDev;
    /*!
     * \brief Devices
     * List of devices found while scanning.
     */
    QList<QBluetoothDeviceInfo> *Devices;
    /*!
     * \brief Socket
     * Socket to communicate with connected bluetooth device.
     */
    QBluetoothSocket *Socket;
    /*!
     * \brief ConnectedDeviceAddress
     * Address of the bluetooth device program is connected to.
     */
    QString ConnectedDeviceAddress;
    /*!
     * \brief Message
     * Message received from the bluetooth device.
     */
    QByteArray *Message;
    /*!
     * \brief StoredData
     * Bytes received from the bluetooth device, later filtered to find message in them.
     */
    QByteArray *StoredData;
};

#endif // BTCOMMUNICATION_H
