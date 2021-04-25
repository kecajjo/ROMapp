#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <iostream>
#include "datatable.h"
#include "dataforplot.h"

#include <vector>
#include <fstream>
#include <cstdlib>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void PlotInit();
    void ReadExampleData();

private slots:
    void RefreshDataTab();
    void RefreshPlots();

private:
    Ui::MainWindow *ui;
    QTimer *Tim;
    DataForPlot *DatPlot;

    std::vector<DataForDataTable> ExampleData;
    int CurrDataSample;

    void RefreshPlotData();
    void RefreshPlotDisplay();
    void SetDataToPlot();
    void AddGraphs();
    void GraphParamInit();
    void GraphParamInitPWM();
    void GraphParamInitEncoder();
    void GraphParamInitGyro();
    void GraphParamInitCompass();
};


void GenerateExampleData();
double fRand(double fMin, double fMax);

#endif // MAINWINDOW_H
