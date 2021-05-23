#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QCloseEvent>
#include <QList>
#include <QtBluetooth/QBluetoothDeviceInfo>
#include <iostream>
#include "datatable.h"
#include "dataforplot.h"
#include "communication.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * \brief The MainWindow class
 * Takes care of application window
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief MainWindow
     * \param[in] parent - parent QWidget
     * initializes signal-slot connections, initializes all widgets
     */
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /*!
     * \brief SetThreadCommunication
     * \param[in] Comm - object used to communicate with worker thread
     */
    void SetThreadCommunication(Communication *Comm){ThreadComm = Comm;}

private slots:
    /*!
     * \brief RefreshDataTab
     * displays in data table updated values
     */
    void RefreshDataTab();
    /*!
     * \brief RefreshPlots
     * replots all graphs basing on changed data
     */
    void RefreshPlots();
    /*!
     * \brief RefreshData
     * Reads Data sent by another thread
     */
    void RefreshData();
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
    /*!
     * \brief RefreshMap
     * Refreshes map by adding a point to the path
    */
    void RefreshMap();

private:
    /*!
     * \brief InitDevBox
     *  Initializes devices box visual parameters
     */
    void InitDevBox();

private:
    Ui::MainWindow *Ui;
    QTimer *TimTable;
    QTimer *TimPlot;
    QTimer *TimReadData;
    QTimer *TimDevBox;
    QTimer *TimMap;
    DataForPlot *DatPlot;
    DataForDataTable CurrData;
    Communication *ThreadComm;
};

#endif // MAINWINDOW_H

