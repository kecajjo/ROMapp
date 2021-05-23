#ifndef BLUETOOTHWIDGET_H
#define BLUETOOTHWIDGET_H

#include <QWidget>
#include <communication.h>

namespace Ui {
class BluetoothWidget;
}

class BluetoothWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BluetoothWidget(QWidget *parent = nullptr);
    ~BluetoothWidget();
    /*!
     * \brief Init
     * Initializes widget and its communication with worker thread
     */
    void Init(Communication *ThreadComm);

private slots:
    /*!
    * \brief ScanButtonClicked
    * Gives scan command to worker thread
    */
    void ScanButtonClicked(){ThreadComm->ScanForDevicesCommand();}
    /*!
    * \brief ConnectButtonClicked
    * Gives connect command to worker thread
    */
    void ConnectButtonClicked();
    /*!
    * \brief DisconnectButtonClicked
    * Gives disconnect command to worker thread
    */
    void DisconnectButtonClicked(){ThreadComm->DisconnectCommand();}
    /*!
    * \brief RefreshDevBox
    * If devices list changed, refreshes data stored in devices box
    */
    void RefreshDevBox();

private:
    Ui::BluetoothWidget *Ui;
    Communication *ThreadComm;

    /*!
     * \brief InitDevBox
     *  Initializes devices box visual parameters
     */
    void InitDevBox();
};

#endif // BLUETOOTHWIDGET_H
