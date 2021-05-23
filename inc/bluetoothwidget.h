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
 * Widget containing options to manage bluetooth connection
 */
class BluetoothWidget : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief BluetoothWidget
     * \param[in] parent
     * Sets signal-slot connections
     */
    explicit BluetoothWidget(QWidget *parent = nullptr);
    ~BluetoothWidget();
    /*!
     * \brief Init
     * \param[in] ThreadComm - variable to communicate with worker thread
     * Initializes communication with worker thread
     */
    void Init(Communication *ThreadComm);

private slots:
    /*!
    * \brief ScanButtonClicked
    * Gives scan command to worker thread
    */
    void ScanButtonClicked();
    /*!
    * \brief ConnectButtonClicked
    * Gives connect command to worker thread
    *
    * Gives connect command to worker thread
    * and starts timers checking if connection was sucessful or timeout happened
    */
    void ConnectButtonClicked();
    /*!
    * \brief DisconnectButtonClicked
    * Gives disconnect command to worker thread and closes the widget
    */
    void DisconnectButtonClicked();
    /*!
    * \brief RefreshDevBox
    * If devices list changed, refreshes data stored in devices box
    */
    void RefreshDevBox();
    /*!
     * \brief closeEvent
     * \param[in] Event - event which trigerred function
     * Reimplemented closing function
     */
    void closeEvent(QCloseEvent *Event);
    /*!
     * \brief ConnectionTimeout
     * Function gives disconnect command
     * stops timer checking if connection was successful
     * and hides loading gif
     */
    void ConnectionTimeout();
    /*!
     * \brief ConnectionCheck
     * Checks if connetion to the device was successful
     *
     * Stops TimConnectionTimer
     * If connection was successful closes widget
     */
    void ConnectionCheck();

private:
    /*!
     * \brief InitDevBox
     *  Initializes devices box visual parameters
     */
    void InitDevBox();

private:
    Ui::BluetoothWidget *Ui;
    Communication *ThreadComm;
    QTimer *TimDevBox;
    QMovie *Loading;
    QTimer *TimConnectionTimeout;
    QTimer *TimConnectionCheck;

signals:
    /*!
     * \brief AboutToClose
     * Signal is trigerred when widget is about to close
     */
    void AboutToClose();

};

#endif // BLUETOOTHWIDGET_H
