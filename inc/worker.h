#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "communication.h"
#include "btcommunication.h"
#include "datatransform.h"


/*!
 * \brief The Worker class
 * Class designed to be executed in the worker thread.
 */
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
     * Emits StartSig.
     */
    void SendStartSig(){emit StartSig();}

public slots:
    /*!
     * \brief Start
     * Initializes signal-slot connections and event checking timer.
     */
    void Start();

private slots:
    /*!
     * \brief CheckEvents
     * Process events thats happend since the last CheckEvents.
     */
    void CheckEvents();
    /*!
     * \brief ScanFinished
     * \param[in] DevLst - list of found devices
     * Tells the main thread that bluetooth devices scan has finished.
     */
    void ScanFinished(QList<QBluetoothDeviceInfo>* DevLst){Comm->ScanFinished(DevLst);}
    /*!
     * \brief DeviceFound
     * Tells the main thread that new device has been found.
     */
    void DeviceFound(){Comm->NewDevice();}
    /*!
     * \brief Connected
     *  Tells the main thread that connection was successfull.
     */
    void Connected(){Comm->Connected();}
    /*!
     * \brief Disconnected
     * Tells the main thread that connection with bluetooth device has ended.
     */
    void Disconnected(){Comm->Disconnected();}
    /*!
     * \brief ConnectionError
     *  Tells the main thread there was connection error.
     */
    void ConnectionError();
    /*!
     * \brief NewDevLst
     * \param[in] Lst - devices list to be available to main thread
     * Updates devices list available to the main thread.
     */
    void NewDevLst(QList<QBluetoothDeviceInfo> *Lst);
    /*!
     * \brief ReceiveMessage
     * \param[in] RawData - data received from bluetooth
     * Converts data received from the bluetooth device and sends it to the main thread.
     */
    void ReceiveMessage(QByteArray *RawData);

signals:
    /*!
     * \brief StartSig
     * Emitting this signal start the worker thread event loop.
     */
    void StartSig();

private:
    /*!
     * \brief Comm
     * Allows to communitate with the main thread.
     */
    Communication *Comm;
    /*!
     * \brief ConvertedData
     * Alows to transform the raw data into DataForDataTable format and calculates the robot's position.
     */
    DataTransform *ConvertedData;
    /*!
     * \brief BT
     * Takes care of the bluetooth communication.
     */
    BTCommunication *BT;
    /*!
     * \brief Tim
     * Checks for commands sent by the main thread.
     */
    QTimer *Tim;
};

#endif // WORKER_H
