#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){

    ui->setupUi(this);
    this->setWindowTitle("ROMapp");

    GenerateExampleData();
    ReadExampleData();
    CurrDataSample = 0;

    DatPlot = new DataForPlot;
    PlotInit();

    DataForDataTable data;
    ui->DataTableW->UpdateDisplay(data);

    Tim = new QTimer;
    connect(Tim, &QTimer::timeout, this, &MainWindow::RefreshDataTab);
    connect(Tim, &QTimer::timeout, this, &MainWindow::RefreshPlots);
    Tim->start(500);//Timer interrupt every 0.5sec
}

MainWindow::~MainWindow(){
    delete DatPlot;
    delete Tim;
    delete ui;
}

void MainWindow::PlotInit(){
    //initializes X axis values
    for(int i=0;i<SAMPLES;i++){
        DatPlot->XAxisGraphVal[i] = i;
    }

    AddGraphs();
    GraphParamInit();//initializes graphs parameteres such as axis range

    SetDataToPlot();//sets data to all gaphs before plotting
    RefreshPlotDisplay();//replots all graphs
}

void MainWindow::ReadExampleData(){
    std::ifstream F("ExDat.txt");
    DataForDataTable Dat;
    int i = 0;
    while(F >> Dat){
        if(i==0){
            Dat.CalcPosition(0,0);
        } else{
            Dat.CalcPosition(ExampleData[i-1].GetPtrPosition());
        }
        ExampleData.push_back(Dat);
        ++i;
    }
    F.close();
}

void MainWindow::RefreshDataTab(){
    CurrDataSample = (CurrDataSample+1)%ExampleData.size();
    ui->DataTableW->UpdateDisplay(ExampleData[CurrDataSample]);
}

void MainWindow::RefreshPlots(){
    RefreshPlotData();//updates values that are plotted
    SetDataToPlot();//sets updated data for plotting
    RefreshPlotDisplay();//replots all graphs
}

void MainWindow::RefreshPlotData(){
    DatPlot->PWMA.removeFirst();
    DatPlot->PWMA.push_back(ExampleData[CurrDataSample].GetPWM(0));
    DatPlot->PWMB.removeFirst();
    DatPlot->PWMB.push_back(ExampleData[CurrDataSample].GetPWM(1));
    DatPlot->EncoderA.removeFirst();
    DatPlot->EncoderA.push_back(ExampleData[CurrDataSample].GetEncoder(0));
    DatPlot->EncoderB.removeFirst();
    DatPlot->EncoderB.push_back(ExampleData[CurrDataSample].GetEncoder(1));
    DatPlot->Gyro.removeFirst();
    DatPlot->Gyro.push_back(ExampleData[CurrDataSample].GetGyro());
    DatPlot->Compass.removeFirst();
    DatPlot->Compass.push_back(ExampleData[CurrDataSample].GetCompass());
}

void MainWindow::RefreshPlotDisplay(){
    ui->PWMPlot->replot();
    ui->EncoderPlot->graph(0)->setData(DatPlot->XAxisGraphVal, DatPlot->EncoderA);
    ui->EncoderPlot->graph(1)->setData(DatPlot->XAxisGraphVal, DatPlot->EncoderB);
    ui->EncoderPlot->replot();
    ui->GyroPlot->replot();
    ui->CompassPlot->replot();
}

void MainWindow::SetDataToPlot(){
    ui->PWMPlot->graph(0)->setData(DatPlot->XAxisGraphVal, DatPlot->PWMA);
    ui->PWMPlot->graph(1)->setData(DatPlot->XAxisGraphVal, DatPlot->PWMB);
    ui->EncoderPlot->graph(0)->setData(DatPlot->XAxisGraphVal, DatPlot->EncoderA);
    ui->EncoderPlot->graph(1)->setData(DatPlot->XAxisGraphVal, DatPlot->EncoderB);
    ui->GyroPlot->graph(0)->setData(DatPlot->XAxisGraphVal, DatPlot->Gyro);
    ui->CompassPlot->graph(0)->setData(DatPlot->XAxisGraphVal, DatPlot->Compass);
}

void MainWindow::AddGraphs(){
    ui->PWMPlot->addGraph();
    ui->PWMPlot->addGraph();
    ui->EncoderPlot->addGraph();
    ui->EncoderPlot->addGraph();
    ui->GyroPlot->addGraph();
    ui->CompassPlot->addGraph();
}

void MainWindow::GraphParamInit(){
    GraphParamInitPWM();
    GraphParamInitEncoder();
    GraphParamInitGyro();
    GraphParamInitCompass();
}

void MainWindow::GraphParamInitPWM(){
    ui->PWMPlot->plotLayout()->insertRow(0);
    ui->PWMPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->PWMPlot, "PWM", QFont("sans", 10, QFont::Bold)));
    ui->PWMPlot->xAxis->setVisible(false);
    ui->PWMPlot->yAxis->setLabel("Value [%]");
    ui->PWMPlot->xAxis->setRange(0, DatPlot->XAxisGraphVal[SAMPLES-1]);
    ui->PWMPlot->yAxis->setRange(0, 100);
    ui->PWMPlot->graph(0)->setPen(QColor(Qt::red));//line color
    ui->PWMPlot->graph(0)->setBrush(QBrush(QColor(200, 50, 50, 80)));//fill color
    ui->PWMPlot->graph(0)->setName("Right motor");//needed for legend
    ui->PWMPlot->graph(1)->setPen(QColor(Qt::green));//line color
    ui->PWMPlot->graph(1)->setBrush(QBrush(QColor(50, 200, 50, 80)));//fill color
    ui->PWMPlot->graph(1)->setName("Left motor");//needed for legend
    ui->PWMPlot->legend->setVisible(true);
    ui->PWMPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignLeft);
    QFont LegendFont = font();
    LegendFont.setPointSize(8);
    ui->PWMPlot->legend->setFont(LegendFont);
}

void MainWindow::GraphParamInitEncoder(){
    ui->EncoderPlot->plotLayout()->insertRow(0);
    ui->EncoderPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->EncoderPlot, "Wheel speed", QFont("sans", 10, QFont::Bold)));
    ui->EncoderPlot->xAxis->setVisible(false);
    ui->EncoderPlot->yAxis->setLabel("Encoder ticks");
    ui->EncoderPlot->xAxis->setRange(0, DatPlot->XAxisGraphVal[SAMPLES-1]);
    ui->EncoderPlot->yAxis->setRange(0, 3);
    ui->EncoderPlot->graph(0)->setPen(QColor(Qt::red));//line color
    ui->EncoderPlot->graph(0)->setBrush(QBrush(QColor(200, 50, 50, 80)));//fill color
    ui->EncoderPlot->graph(0)->setName("Right wheel");
    ui->EncoderPlot->graph(1)->setPen(QColor(Qt::green));//line color
    ui->EncoderPlot->graph(1)->setBrush(QBrush(QColor(50, 200, 50, 80)));//fill color
    ui->EncoderPlot->graph(1)->setName("Left wheel");
    ui->EncoderPlot->legend->setVisible(true);
    ui->EncoderPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignLeft);
    QFont LegendFont = font();
    LegendFont.setPointSize(8);
    ui->EncoderPlot->legend->setFont(LegendFont);
}

void MainWindow::GraphParamInitGyro(){
    ui->GyroPlot->plotLayout()->insertRow(0);
    ui->GyroPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->GyroPlot, "Gyroscope", QFont("sans", 10, QFont::Bold)));
    ui->GyroPlot->xAxis->setVisible(false);
    ui->GyroPlot->xAxis->setRange(0, DatPlot->XAxisGraphVal[SAMPLES-1]);
    ui->GyroPlot->yAxis->setRange(0, 120);
    ui->GyroPlot->graph(0)->setPen(QColor(Qt::blue));//line color
    ui->GyroPlot->graph(0)->setBrush(QBrush(QColor(50, 50, 200, 80)));//fill color
}

void MainWindow::GraphParamInitCompass(){
    ui->CompassPlot->plotLayout()->insertRow(0);
    ui->CompassPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->CompassPlot, "Compass", QFont("sans", 10, QFont::Bold)));
    ui->CompassPlot->xAxis->setVisible(false);
    ui->CompassPlot->xAxis->setRange(0, DatPlot->XAxisGraphVal[SAMPLES-1]);
    ui->CompassPlot->yAxis->setRange(0, 360);
    ui->CompassPlot->graph(0)->setPen(QColor(Qt::blue));//line color
    ui->CompassPlot->graph(0)->setBrush(QBrush(QColor(50, 50, 200, 80)));//fill color
}


void GenerateExampleData(){
    std::ofstream F("ExDat.txt");
    srand (time(NULL));
    double tab[6];
    for(int i=0;i<100;i++){
        tab[0] = fRand(0.01, 99.8);
        tab[1] = fRand(0.01, 99.8);
        tab[2] = fRand(0.01, 2.03);
        tab[3] = fRand(0.01, 2.03);
        tab[4] = fRand(0.01, 119.8);
        tab[5] = fRand(0.01, 359.8);
        for(int j=0;j<6;j++){
            F << tab[j] << " ";
        }
        F << std::endl;
    }
    F.close();
}
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

