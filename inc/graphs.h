#ifndef GRAPHS_H
#define GRAPHS_H

#include <QWidget>
#include "qcustomplot.h"
#include "dataforplot.h"
#include "datafordatatable.h"

namespace Ui {
class Graphs;
}

/*!
 * \brief The Graphs class
 * Class responsible for the graphs widget.
 */
class Graphs : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Graphs
     * \param[in] parent - parent QWidget
     */
    explicit Graphs(QWidget *parent = nullptr);
    ~Graphs();

public slots:
    /*!
     * \brief PlotInit
     * \param[in] DatPlot - data which will store data to be plotted
     * Initializes graphs and displays them, initializes the time axis data.
     */
    void PlotInit(DataForPlot *DatPlot);
    /*!
     * \brief SetDataToPlot
     * \param[in] DatPlot - data used to plot graphs
     * Sets which vector from DataForPlot will be plotted on which graph.
     *
     * NOTE: this function needs to be used before refreshing display if the data has changed.
     */
    void SetDataToPlot(DataForPlot *DatPlot);
    /*!
     * \brief RefreshPlots
     * \param[in] CurrData - data to be added to graphs
     * Replots all graphs basing on the changed data.
     */
    void RefreshPlots(DataForDataTable CurrData);
    /*!
     * \brief RefreshPlotDisplay
     * Displays graphs basing on the current data.
     *
     * NOTE: data needs to be assigned first.
     * If there is new data, use SetDataToPlot() function first.
     */
    void RefreshPlotDisplay();

private:
    /*!
     * \brief RefreshPlotData
     * \param[in] CurrData - new data to be added to graphs
     * Shifts all plotted data by 1 sample left.
     *
     * Shifts data to be plotted left by removing first sample,
     * adds new sample as last element in QVector.
     */
    void RefreshPlotData(DataForDataTable CurrData);
    /*!
     * \brief GraphParamInit
     * Initializes graphs parameters such as titles, axes, legends.
     *
     * Initializes graphs basing on parameters set in graph param init functions
     * such as GraphParamInitPWM.
     */
    void GraphParamInit();
    /*!
     * \brief AddGraphs
     * Adds number of plots(data sets) to each graph.
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
     * Initializes Compass graph visual parameters such as title, legend etc.
     *
     * adds graph title
     * sets X axis invisible
     * sets X and Y axis ranges
     * sets plot line color and fill
     */
    void GraphParamInitCompass();

    /*!
     * \brief ui
     * Contains information about the UI.
     */
    Ui::Graphs *ui;
    /*!
     * \brief DatPlot
     * Ploted data.
     */
    DataForPlot *DatPlot;

};
#endif // GRAPHS_H
