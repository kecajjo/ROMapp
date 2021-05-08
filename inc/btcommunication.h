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
    void ReadData();
    void DiscoveryError(QBluetoothDeviceDiscoveryAgent::Error Err);
    void ScanEnded();

signals:
    void ScanFinished(QList<QBluetoothDeviceInfo>*);
    void ServiceDisconnected();
    void ServiceConnected();
    void ConnectionError();
    void NewDevice(QBluetoothDeviceInfo);
    void NewDevLst(QList<QBluetoothDeviceInfo>*);

private:
    QBluetoothDeviceDiscoveryAgent *DiscoveryAgent;
    QBluetoothLocalDevice *LocDev;
    QList<QBluetoothDeviceInfo> *Devices;
    QBluetoothSocket *Socket;
    QString ConnectedDeviceAddress;
};

#endif // BTCOMMUNICATION_H
