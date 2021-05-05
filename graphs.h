#ifndef GRAPHS_H
#define GRAPHS_H

#include <QWidget>
#include "qcustomplot.h"
#include "dataforplot.h"
#include "datafordatatable.h"

namespace Ui {
class Graphs;
}

class Graphs : public QWidget
{
    Q_OBJECT
public:
    explicit Graphs(QWidget *parent = nullptr);
    ~Graphs();

public slots:
    /*!
     * \brief PlotInit
     * initializes Graphs and displays them
     */
    void PlotInit(DataForPlot *DatPlot);
    /*!
     * \brief RefreshPlotData
     * shifts all plotted data by 1 sample left
     *
     * shifts data to be plotted left by removing first sample
     * adds new sample as last element in QVector
     */
    void RefreshPlotData(DataForDataTable CurrData);/*!
     * \brief SetDataToPlot
     * sets which vector from DataForPlot will be plotted on which graph
     *
     * NOTE: this function needs to be used before refreshing display if data has changed
     */
    void SetDataToPlot(DataForPlot *DatPlot);
    /*!
     * \brief RefreshPlots
     * replots all graphs basing on changed data
     */
    void RefreshPlots(DataForDataTable CurrData);
    /*!
     * \brief RefreshPlotDisplay
     * Displays graphs basing on current data
     *
     * NOTE: data needs to be assigned first
     * if there is new data, use SetDataToPlot() function first
     */
    void RefreshPlotDisplay();

private:
    Ui::Graphs *ui;
    DataForPlot *DatPlot;
    /*!
     * \brief GraphParamInit
     * Initializes graphs parameters such as titles, axes, legends
     *
     * Initializes graphs basing on parameters set in graph param init functions
     * such as GraphParamInitPWM
     */
    void GraphParamInit();
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
#endif // GRAPHS_H
