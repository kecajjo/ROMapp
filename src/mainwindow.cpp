#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , Ui(new Ui::MainWindow){

    Ui->setupUi(this);
    this->setWindowTitle("ROMapp");

    DatPlot = new DataForPlot;
    Ui->GraphsW->PlotInit(DatPlot);
    DataForDataTable Data;
    Ui->DataTableW->UpdateDisplay(Data);
    Ui->DevicesBox->setInsertPolicy(QComboBox::InsertAtBottom);

    TimTable = new QTimer;
    TimPlot = new QTimer;
    TimReadData = new QTimer;
    TimDevBox = new QTimer;
    TimMap = new QTimer;

    InitDevBox();

    connect(TimTable, &QTimer::timeout, this, &MainWindow::RefreshDataTab);
    connect(TimPlot, &QTimer::timeout, this, &MainWindow::RefreshPlots);
    connect(TimReadData, &QTimer::timeout, this, &MainWindow::RefreshData);
    connect(TimDevBox, &QTimer::timeout, this, &MainWindow::RefreshDevBox);
    connect(TimMap, &QTimer::timeout, this, &MainWindow::RefreshMap);
    connect(Ui->ScanButton, &QAbstractButton::clicked, this, &MainWindow::ScanButtonClicked);
    connect(Ui->ConnectButton, &QAbstractButton::clicked, this, &MainWindow::ConnectButtonClicked);
    connect(Ui->DisconnectButton, &QAbstractButton::clicked, this, &MainWindow::DisconnectButtonClicked);
    TimTable->start(1000);//Timer event every 1sec
    TimPlot->start(50);//Timer event every 0.05sec
    TimReadData->start(50);//Timer event every 0.05sec
    TimDevBox->start(1000);//Timer event every 1sec
    TimMap->start(50);

}

MainWindow::~MainWindow(){
    delete DatPlot;
    delete TimTable;
    delete TimPlot;
    delete TimReadData;
    delete TimDevBox;
    delete TimMap;
    delete Ui;
}

void MainWindow::RefreshDataTab(){
    Ui->DataTableW->UpdateDisplay(CurrData);
}

void MainWindow::RefreshPlots(){
    Ui->GraphsW->RefreshPlots(CurrData);
}

void MainWindow::RefreshData(){
    CurrData = ThreadComm->ReadData();
}

void MainWindow::ConnectButtonClicked(){
    int Idx = Ui->DevicesBox->currentIndex();
    ThreadComm->ConnectToDeviceCommand(Idx);
}

void MainWindow::RefreshDevBox(){
    if(ThreadComm->IsDevLstChanged()){
        ThreadComm->ClearDevLstChanged();
        QList<QString> DevBox;
        Ui->DevicesBox->clear();
        QList<QBluetoothDeviceInfo> *DevInf = ThreadComm->GetDevices();
        if(DevInf != nullptr){
            if(DevInf->length() != 0){
                QList<QBluetoothDeviceInfo>::iterator Iter;
                for(Iter=DevInf->begin(); Iter!=DevInf->end(); Iter++){
                    DevBox.append(QString(Iter->name()));
                }
                Ui->DevicesBox->addItems(DevBox);
            }
        }
    }
}

void MainWindow::RefreshMap(){
    Ui->MapW->AddPoint(CurrData.GetPosition(0), CurrData.GetPosition(1));
}

void MainWindow::InitDevBox(){
    Ui->DevicesBox->setMaxVisibleItems(5);
}
