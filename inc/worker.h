#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "communication.h"
#include "btcommunication.h"
#include "datatransform.h"

class Worker : public QObject{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker();
    void SetCommunication(Communication *Comm){this->Comm = Comm;}
    void SendStartSig(){emit StartSig();}

public slots:
    void Start();

private slots:
    void CheckEvents();
    void ScanFinished(QList<QBluetoothDeviceInfo>* DevLst){Comm->ScanFinished(DevLst);}
    void DeviceFound(){Comm->NewDevice();}
    void Connected(){Comm->Connected();}
    void Disconnected(){Comm->Disconnected();}
    void ConnectionError();
    void NewDevLst(QList<QBluetoothDeviceInfo>*);

signals:
    void StartSig();

private:
    Communication *Comm;
    DataTransform *ConvertedData;
    BTCommunication *BT;
    QTimer *Tim;
};

#endif // WORKER_H
