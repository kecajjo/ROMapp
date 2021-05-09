#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "communication.h"
#include "btcommunication.h"
#include "datatransform.h"

class Worker : public QObject{
    Q_OBJECT
public:
    /*!
     * \brief Worker
     * \param[in] parent - parent QObject
     */
    explicit Worker(QObject *parent = nullptr);
    ~Worker();
    /*!
     * \brief SetCommunication
     * \param[in] Comm - object used to communicate with main thread
     */
    void SetCommunication(Communication *Comm){this->Comm = Comm;}
    /*!
     * \brief SendStartSig
     * Emits StartSig
     */
    void SendStartSig(){emit StartSig();}

public slots:
    /*!
     * \brief Start
     * Initializes signal-slot connections and event checking timer
     */
    void Start();

private slots:
    /*!
     * \brief CheckEvents
     * Process events thats happend since last CheckEvents
     */
    void CheckEvents();
    /*!
     * \brief ScanFinished
     * \param[in] DevLst - list of found devices
     * Tells main thread that bluetooth devices scan has finished
     */
    void ScanFinished(QList<QBluetoothDeviceInfo>* DevLst){Comm->ScanFinished(DevLst);}
    /*!
     * \brief DeviceFound
     * Tells main thread that new device has been found
     */
    void DeviceFound(){Comm->NewDevice();}
    /*!
     * \brief Connected
     *  Tells main thread that connection was successfull
     */
    void Connected(){Comm->Connected();}
    /*!
     * \brief Disconnected
     * Tells main thread that connection with bluetooth device has ended
     */
    void Disconnected(){Comm->Disconnected();}
    /*!
     * \brief ConnectionError
     *  Tells main thread there was connection error
     */
    void ConnectionError();
    /*!
     * \brief NewDevLst
     * \param[in] Lst - devices list to be available to main thread
     * Updates devices list available to main thread
     */
    void NewDevLst(QList<QBluetoothDeviceInfo> *Lst);
    /*!
     * \brief ReceiveMessage
     * \param RawData - data received from bluetooth
     * Converts data received from bluetooth and sends it to main thread
     */
    void ReceiveMessage(QByteArray *RawData);

signals:
    /*!
     * \brief StartSig
     * Emitting this signal start worker thread event loop
     */
    void StartSig();

private:
    Communication *Comm;
    DataTransform *ConvertedData;
    BTCommunication *BT;
    QTimer *Tim;
};

#endif // WORKER_H
