#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>
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
    /*!
     * \brief PlotInit
     * initializes Graphs and displays them
     */
    void PlotInit();

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
     * \brief GraphParamInit
     * Initializes graphs parameters such as titles, axes, legends
     *
     * Initializes graphs basing on parameters set in graph param init functions
     * such as GraphParamInitPWM
     */
    void GraphParamInit();
    /*!
     * \brief RefreshPlotData
     * shifts all plotted data by 1 sample left
     *
     * shifts data to be plotted left by removing first sample
     * adds new sample as last element in QVector
     */
    void RefreshPlotData();

    /*!
     * \brief RefreshData
     * Reads Data sent by another thread
     */
    void RefreshData();

private:
    Ui::MainWindow *ui;
    QTimer *TimTable;
    QTimer *TimPlot;
    QTimer *TimReadData;
    DataForPlot *DatPlot;
    DataForDataTable CurrData;
    Communication *ThreadComm;

    /*!
     * \brief RefreshPlotDisplay
     * Displays graphs basing on current data
     *
     * NOTE: data needs to be assigned first
     * if there is new data, use SetDataToPlot() function first
     */
    void RefreshPlotDisplay();
    /*!
     * \brief SetDataToPlot
     * sets which vector from DataForPlot will be plotted on which graph
     *
     * NOTE: this function needs to be used before refreshing display if data has changed
     */
    void SetDataToPlot();
    /*!
     * \brief AddGraphs
     * adds number of plots(data sets) to each graph
     */
    void AddGraphs();
    /*!
     * \brief GraphParamInitPWM
     * Initializes PWM graph visual parameters such as title, legend etc.
     *
     * adds graph title
     * sets X Axis invisible
     * sets X and Y axis ranges
     * sets plot line color and fill
     * adds legend
     * adds Y axis label
     */
    void GraphParamInitPWM();
    /*!
     * \brief GraphParamInitEncoder
     * Initializes Encoder graph visual parameters such as title, legend etc.
     *
     * adds graph title
     * sets X Axis invisible
     * sets X and Y axis ranges
     * sets plot line color and fill
     * adds legend
     * adds Y axis label
     */
    void GraphParamInitEncoder();
    /*!
     * \brief GraphParamInitGyro
     * Initializes Gyroscope graph visual parameters such as title, legend etc.
     *
     * adds graph title
     * sets X axis invisible
     * sets X and Y axis ranges
     * sets plot line color and fill
     */
    void GraphParamInitGyro();
    /*!
     * \brief GraphParamInitCompass
     *  Initializes Compass graph visual parameters such as title, legend etc.
     *
     * adds graph title
     * sets X axis invisible
     * sets X and Y axis ranges
     * sets plot line color and fill
     */
    void GraphParamInitCompass();
};

#endif // MAINWINDOW_H
