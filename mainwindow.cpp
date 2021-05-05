#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){

    ui->setupUi(this);
    this->setWindowTitle("ROMapp");

    DatPlot = new DataForPlot;
    ui->GraphsW->PlotInit(DatPlot);
    DataForDataTable Data;
    ui->DataTableW->UpdateDisplay(Data);

    TimTable = new QTimer;
    TimPlot = new QTimer;
    TimReadData = new QTimer;
    connect(TimTable, &QTimer::timeout, this, &MainWindow::RefreshDataTab);
    connect(TimPlot, &QTimer::timeout, this, &MainWindow::RefreshPlots);
    connect(TimReadData, &QTimer::timeout, this, &MainWindow::RefreshData);
    connect(ui->ScanButton, &QAbstractButton::clicked, this, &MainWindow::ScanButtonClicked);
    connect(ui->ConnectButton, &QAbstractButton::clicked, this, &MainWindow::ConnectButtonClicked);
    connect(ui->DisconnectButton, &QAbstractButton::clicked, this, &MainWindow::DisconnectButtonClicked);
    TimTable->start(1000);//Timer interrupt every 1sec
    TimPlot->start(50);//Timer interrupt every 0.1sec
    TimReadData->start(50);//Timer interrupt every 0.1sec
}

MainWindow::~MainWindow(){
    delete DatPlot;
    delete TimTable;
    delete TimPlot;
    delete TimReadData;
    delete ui;
}

void MainWindow::RefreshDataTab(){
    ui->DataTableW->UpdateDisplay(CurrData);
}

void MainWindow::RefreshPlots(){
    ui->GraphsW->RefreshPlots(CurrData);
}

void MainWindow::RefreshData(){
    CurrData = ThreadComm->ReadData();
}

void MainWindow::ConnectButtonClicked(){
    ThreadComm->ConnectToDeviceCommand(0);//for now constant value later it will be retrived from combo box
}

void MainWindow::closeEvent(QCloseEvent* Event){
    ThreadComm->Exit();
    Event->accept();
}
