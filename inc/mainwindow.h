#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QCloseEvent>
#include <QList>
#include <QtBluetooth/QBluetoothDeviceInfo>
#include <iostream>
#include <QPixmap>
#include <QTransform>
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
 * Takes care of the application window.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief MainWindow
     * \param[in] parent - parent QWidget
     * Initializes signal-slot connections, initializes all widgets.
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
     * Refreshes display and data stored in the DataTable widget.
     */
    void RefreshDataTab();
    /*!
     * \brief RefreshPlots
     * Replots all graphs basing on changed data.
     */
    void RefreshPlots();
    /*!
     * \brief RefreshData
     * Reads data sent by the worker thread.
     */
    void RefreshData();
    /*!
     * \brief RefreshMap
     * Refreshes the map by adding a point to the path
    */
    void RefreshMap();
    /*!
     * \brief OpenBluetoothWindow
     * Opens window that allows to manage bluetooth connection.
     */
    void OpenConnectionWindow();
    /*!
     * \brief closeEvent
     * \param Event - event which trigerred function
     * Reimplemented closing function, closes all windows that were open.
     */
    void closeEvent(QCloseEvent *Event);

private:
    /*!
     * \brief Ui
     * Contains information about the UI.
     */
    Ui::MainWindow *Ui;
    /*!
     * \brief TimTable
     * Timer responsible for refreshing table with the robot data.
     */
    QTimer *TimTable;
    /*!
     * \brief TimPlot
     * Timer responsible for refreshing plots.
     */
    QTimer *TimPlot;
    /*!
     * \brief TimReadData
     * Timer responsible for reading data sent by the worker thread.
     */
    QTimer *TimReadData;
    /*!
     * \brief TimMap
     * Timer responsible for refreashing the map.
     */
    QTimer *TimMap;
    /*!
     * \brief DatPlot
     * Data which is plotted.
     */
    DataForPlot *DatPlot;
    /*!
     * \brief CurrData
     * Data which is shown in the DataTable widget.
     */
    DataForDataTable CurrData;
    /*!
     * \brief ThreadComm
     * Allows to communicate with the worker thread.
     */
    Communication *ThreadComm;

};

#endif // MAINWINDOW_H

