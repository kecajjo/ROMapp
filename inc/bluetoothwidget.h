#ifndef BLUETOOTHWIDGET_H
#define BLUETOOTHWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QCloseEvent>
#include <QMovie>
#include <QLabel>
#include <QDir>
#include <communication.h>
#include <unistd.h>

namespace Ui {
class BluetoothWidget;
}

/*!
 * \brief The BluetoothWidget class
 * Widget containing options to manage the bluetooth connection.
 * Used as separate window.
 */
class BluetoothWidget : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief BluetoothWidget
     * \param[in] parent
     * Sets all necessary signal-slot connections.
     */
    explicit BluetoothWidget(QWidget *parent = nullptr);
    ~BluetoothWidget();
    /*!
     * \brief Init
     * \param[in] ThreadComm - variable to communicate with worker thread
     * Initializes communication with the worker thread.
     */
    void Init(Communication *ThreadComm);

private slots:
    /*!
    * \brief ScanButtonClicked
    * Makes the worker thread scan for bluetooth devices.
    */
    void ScanButtonClicked();
    /*!
    * \brief ConnectButtonClicked
    * Gives connect command to the worker thread.
    *
    * Makes the worker thread connect to the device currently being chosen in the devices combo box
    * and starts timers checking if connection was sucessful or timeout happened.
    */
    void ConnectButtonClicked();
    /*!
    * \brief DisconnectButtonClicked
    * Makes the worker thread disconnect from BT device.
    */
    void DisconnectButtonClicked();
    /*!
    * \brief RefreshDevBox
    * If devices list changed, refreshes data stored in the devices box.
    */
    void RefreshDevBox();
    /*!
     * \brief closeEvent
     * \param[in] Event - event which trigerred function
     * Reimplemented closing function.
     */
    void closeEvent(QCloseEvent *Event);
    /*!
     * \brief ConnectionTimeout
     * Function gives disconnect command,
     * stops timer checking if connection was successful
     * and hides loading gif.
     */
    void ConnectionTimeout();
    /*!
     * \brief ConnectionCheck
     * Checks if connetion to the device was successful.
     *
     * Stops TimConnectionTimer.
     * If connection was successful closes the widget.
     */
    void ConnectionCheck();

private:
    /*!
     * \brief InitDevBox
     *  Initializes devices box visual parameters.
     */
    void InitDevBox();

private:
    /*!
     * \brief Ui
     * Variable responsible for the Ui from the form file.
     */
    Ui::BluetoothWidget *Ui;
    /*!
     * \brief ThreadComm
     * Allows for sending and receiving information from the other thread.
     */
    Communication *ThreadComm;
    /*!
     * \brief TimDevBox
     * Timer responsible for refreashing the devices combo box.
     */
    QTimer *TimDevBox;
    /*!
     * \brief Loading
     * Loading gif
     */
    QMovie *Loading;
    /*!
     * \brief TimConnectionTimeout
     * Timer checks if trying to connect was too long.
     *
     * If device wont be connected before this timer runs out,
     * device is disconnected (program stops to try to connect).
     */
    QTimer *TimConnectionTimeout;
    /*!
     * \brief TimConnectionCheck
     * Polling to check if connection was successful.
     */
    QTimer *TimConnectionCheck;

signals:
    /*!
     * \brief AboutToClose
     * Signal is trigerred when the widget is about to close.
     */
    void AboutToClose();

};

#endif // BLUETOOTHWIDGET_H
