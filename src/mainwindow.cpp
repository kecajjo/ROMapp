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
    WindRoseImg.load(QDir().absoluteFilePath("../ROMapp/fig/wind_rose.png"));
    Ui->DataTableW->UpdateDisplay(Data);
    Ui->WindRose->setAlignment(Qt::AlignCenter);

    TimTable = new QTimer;
    TimPlot = new QTimer;
    TimReadData = new QTimer;
    TimMap = new QTimer;

    connect(TimTable, &QTimer::timeout, this, &MainWindow::RefreshDataTab);
    connect(TimPlot, &QTimer::timeout, this, &MainWindow::RefreshPlots);
    connect(TimReadData, &QTimer::timeout, this, &MainWindow::RefreshData);
    connect(TimMap, &QTimer::timeout, this, &MainWindow::RefreshMap);
    connect(Ui->ActionConnection, &QAction::triggered, this, &MainWindow::OpenConnectionWindow);
    connect(Ui->ActionExit, &QAction::triggered, this, &MainWindow::close);
    TimTable->start(1000);//Timer event every 1sec
    TimPlot->start(50);//Timer event every 0.05sec
    TimReadData->start(50);//Timer event every 0.05sec
    TimMap->start(50);//Timer event every 0.05sec
}

MainWindow::~MainWindow(){
    delete DatPlot;
    delete TimTable;
    delete TimPlot;
    delete TimReadData;
    delete TimMap;
    delete Ui;
}

void MainWindow::SetThreadCommunication(Communication *Comm){
    ThreadComm = Comm;
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

void MainWindow::RefreshMap(){
    Ui->MapW->AddPoint(CurrData.GetPosition(0), CurrData.GetPosition(1));
    RotateWindRose();
}

void MainWindow::OpenConnectionWindow(){
    BluetoothWidget *Wdg = new BluetoothWidget;
    Wdg->Init(ThreadComm);
    Wdg->setWindowModality(Qt::ApplicationModal);
    connect(Wdg, SIGNAL(AboutToClose()), Wdg, SLOT(deleteLater()));
    Wdg->show();
}
void MainWindow::closeEvent(QCloseEvent *Event){
    ThreadComm->End();
    Event->accept();
}

void MainWindow::RotateWindRose(){
    QTransform Rot;
    QPixmap Tmp = WindRoseImg.scaled(Ui->WindRose->width(), Ui->WindRose->height());
    Rot.rotate(-1*CurrData.GetHeading());
    Tmp = Tmp.transformed(Rot);
    Ui->WindRose->setPixmap(Tmp);
}
