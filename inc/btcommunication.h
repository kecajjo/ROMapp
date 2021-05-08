#ifndef BTCOMMUNICATION_H
#define BTCOMMUNICATION_H

#include <QtBluetooth>

class BTCommunication : public QObject{
    Q_OBJECT
public:
    BTCommunication(QObject *parent = nullptr);
    ~BTCommunication();
    void StartScan();
    void ConnectToDevice(const QBluetoothDeviceInfo &Device);
    void Disconnect(){Socket->close();}
private slots:
    void AddDeviceToList(const QBluetoothDeviceInfo &NewDevice);
    void FinishedScan();
    void ServiceConnected();
    void ServiceDisconnected();
    void ReadData();
    void DiscoveryError(QBluetoothDeviceDiscoveryAgent::Error Err);

private:
    QBluetoothDeviceDiscoveryAgent *DiscoveryAgent;
    QBluetoothLocalDevice *LocDev;
    QList<QBluetoothDeviceInfo> *Devices;
    QBluetoothSocket *Socket;
    QString ConnectedDeviceAddress;
};

#endif // BTCOMMUNICATION_H
