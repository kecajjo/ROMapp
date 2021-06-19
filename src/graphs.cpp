#include "graphs.h"
#include "ui_graphs.h"

Graphs::Graphs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graphs){

    ui->setupUi(this);
}

Graphs::~Graphs()
{
    delete ui;
}

void Graphs::PlotInit(DataForPlot *DatPlot){
    this->DatPlot = DatPlot;
    //initializes X axis values
    for(int i=0;i<SAMPLES;i++){
        this->DatPlot->XAxisGraphVal[i] = i;
    }

    AddGraphs();
    GraphParamInit();//initializes graphs parameteres such as axis range
}

void Graphs::RefreshPlotData(DataForDataTable CurrData){
    DatPlot->PWMA.removeFirst();
    DatPlot->PWMA.push_back(CurrData.GetPWM(0));
    DatPlot->PWMB.removeFirst();
    DatPlot->PWMB.push_back(CurrData.GetPWM(1));
    DatPlot->EncoderA.removeFirst();
    DatPlot->EncoderA.push_back(CurrData.GetEncoder(0));
    DatPlot->EncoderB.removeFirst();
    DatPlot->EncoderB.push_back(CurrData.GetEncoder(1));
    DatPlot->Gyro.removeFirst();
    DatPlot->Gyro.push_back(CurrData.GetGyro());
    DatPlot->Compass.removeFirst();
    DatPlot->Compass.push_back(CurrData.GetCompass());
}

void Graphs::RefreshPlots(DataForDataTable CurrData){
    RefreshPlotData(CurrData);//updates values that are plotted
    SetDataToPlot(DatPlot);//sets updated data for plotting
    RefreshPlotDisplay();//replots all graphs
}

void Graphs::RefreshPlotDisplay(){
    ui->PWMPlot->replot();
    ui->EncoderPlot->graph(0)->setData(DatPlot->XAxisGraphVal, DatPlot->EncoderA);
    ui->EncoderPlot->graph(1)->setData(DatPlot->XAxisGraphVal, DatPlot->EncoderB);
    ui->EncoderPlot->replot();
    ui->GyroPlot->replot();
    ui->CompassPlot->replot();
}

void Graphs::SetDataToPlot(DataForPlot *DatPlot){
    this->DatPlot = DatPlot;
    ui->PWMPlot->graph(0)->setData(DatPlot->XAxisGraphVal, DatPlot->PWMA);
    ui->PWMPlot->graph(1)->setData(DatPlot->XAxisGraphVal, DatPlot->PWMB);
    ui->EncoderPlot->graph(0)->setData(DatPlot->XAxisGraphVal, DatPlot->EncoderA);
    ui->EncoderPlot->graph(1)->setData(DatPlot->XAxisGraphVal, DatPlot->EncoderB);
    ui->GyroPlot->graph(0)->setData(DatPlot->XAxisGraphVal, DatPlot->Gyro);
    ui->CompassPlot->graph(0)->setData(DatPlot->XAxisGraphVal, DatPlot->Compass);
}

void Graphs::AddGraphs(){
    ui->PWMPlot->addGraph();
    ui->PWMPlot->addGraph();
    ui->EncoderPlot->addGraph();
    ui->EncoderPlot->addGraph();
    ui->GyroPlot->addGraph();
    ui->CompassPlot->addGraph();
}

void Graphs::GraphParamInit(){
    GraphParamInitPWM();
    GraphParamInitEncoder();
    GraphParamInitGyro();
    GraphParamInitCompass();
}

void Graphs::GraphParamInitPWM(){
    QPixmap Background(QDir().absoluteFilePath("../ROMapp/fig/background.jpg"));
    QRect Cut(0,51,811,800);
    Background = Background.copy(Cut);
    ui->PWMPlot->setBackground(Background);
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
    ui->PWMPlot->yAxis->grid()->setPen(QPen(QColor(20,20,20,255),1,Qt::DotLine));
}

void Graphs::GraphParamInitEncoder(){
    QPixmap Background(QDir().absoluteFilePath("../ROMapp/fig/background.jpg"));
    QRect Cut(0,231,811,800);
    Background = Background.copy(Cut);
    ui->EncoderPlot->setBackground(Background);
    ui->EncoderPlot->plotLayout()->insertRow(0);
    ui->EncoderPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->EncoderPlot, "Wheel speed", QFont("sans", 10, QFont::Bold)));
    ui->EncoderPlot->xAxis->setVisible(false);
    ui->EncoderPlot->yAxis->setLabel("cm/s");
    ui->EncoderPlot->xAxis->setRange(0, DatPlot->XAxisGraphVal[SAMPLES-1]);
    ui->EncoderPlot->yAxis->setRange(-15, 15);
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
    ui->EncoderPlot->yAxis->grid()->setPen(QPen(QColor(20,20,20,255),1,Qt::DotLine));
}

void Graphs::GraphParamInitGyro(){
    QPixmap Background(QDir().absoluteFilePath("../ROMapp/fig/background.jpg"));
    QRect Cut(0,411,811,800);
    Background = Background.copy(Cut);
    ui->GyroPlot->setBackground(Background);
    ui->GyroPlot->plotLayout()->insertRow(0);
    ui->GyroPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->GyroPlot, "Gyroscope", QFont("sans", 10, QFont::Bold)));
    ui->GyroPlot->xAxis->setVisible(false);
    ui->GyroPlot->xAxis->setRange(0, DatPlot->XAxisGraphVal[SAMPLES-1]);
    ui->GyroPlot->yAxis->setRange(-250, 250);
    ui->GyroPlot->graph(0)->setPen(QColor(Qt::blue));//line color
    ui->GyroPlot->graph(0)->setBrush(QBrush(QColor(50, 50, 200, 80)));//fill color
    ui->GyroPlot->yAxis->setLabel("Value [°/s]");
    ui->GyroPlot->yAxis->grid()->setPen(QPen(QColor(20,20,20,255),1,Qt::DotLine));
}

void Graphs::GraphParamInitCompass(){
    QPixmap Background(QDir().absoluteFilePath("../ROMapp/fig/background.jpg"));
    QRect Cut(0,591,811,800);
    Background = Background.copy(Cut);
    ui->CompassPlot->setBackground(Background);
    ui->CompassPlot->plotLayout()->insertRow(0);
    ui->CompassPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->CompassPlot, "Compass", QFont("sans", 10, QFont::Bold)));
    ui->CompassPlot->xAxis->setVisible(false);
    ui->CompassPlot->xAxis->setRange(0, DatPlot->XAxisGraphVal[SAMPLES-1]);
    ui->CompassPlot->yAxis->setRange(-180, 180);
    ui->CompassPlot->graph(0)->setPen(QColor(Qt::blue));//line color
    ui->CompassPlot->graph(0)->setBrush(QBrush(QColor(50, 50, 200, 80)));//fill color
    ui->CompassPlot->yAxis->setLabel("Value [°]");
    ui->CompassPlot->yAxis->grid()->setPen(QPen(QColor(20,20,20,255),1,Qt::DotLine));
}

