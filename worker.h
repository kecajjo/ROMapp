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

private:
    Communication *Comm;
    DataTransform *ConvertedData;
    BTCommunication *BT;
    QTimer *Tim;

signals:
    void StartSig();
};

#endif // WORKER_H
