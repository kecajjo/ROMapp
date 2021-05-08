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
 * TODO
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

    void ScanButtonClicked(){ThreadComm->ScanForDevicesCommand();}

    void ConnectButtonClicked();

    void DisconnectButtonClicked(){ThreadComm->DisconnectCommand();}

    void RefreshDevBox();

private:
    void InitDevBox();

private:
    Ui::MainWindow *Ui;
    QTimer *TimTable;
    QTimer *TimPlot;
    QTimer *TimReadData;
    QTimer *TimDevBox;
    DataForPlot *DatPlot;
    DataForDataTable CurrData;
    Communication *ThreadComm;
};

#endif // MAINWINDOW_H

