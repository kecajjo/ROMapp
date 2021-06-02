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
#include "bluetoothwidget.h"
#include <memory>

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
    void SetThreadCommunication(Communication *Comm);

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
     * \brief RefreshMap
     * Refreshes map by adding a point to the path
    */
    void RefreshMap();
    /*!
     * \brief OpenBluetoothWindow
     * Opens window that allows to manage connection
     */
    void OpenConnectionWindow();
    /*!
     * \brief closeEvent
     * \param Event - event which trigerred function
     * Reimplemented closing function, closes all windows that were open
     */
    void closeEvent(QCloseEvent *Event);

private:
    /*!
     * \brief Ui
     * Contains information about UI
     */
    Ui::MainWindow *Ui;
    /*!
     * \brief TimTable
     * Timer responsible for refreshing table with robot data
     */
    QTimer *TimTable;
    /*!
     * \brief TimPlot
     * Timer responsible for refreshing plots
     */
    QTimer *TimPlot;
    /*!
     * \brief TimReadData
     * Timer responsible for reading data sent by worker thread
     */
    QTimer *TimReadData;
    /*!
     * \brief TimMap
     * Timer responsible for refreashing map
     */
    QTimer *TimMap;
    /*!
     * \brief DatPlot
     * Data which is plotted
     */
    DataForPlot *DatPlot;
    /*!
     * \brief CurrData
     * Data which is shown in the table
     */
    DataForDataTable CurrData;
    /*!
     * \brief ThreadComm
     * Allows to communicate with worker thread
     */
    Communication *ThreadComm;

};

#endif // MAINWINDOW_H

