#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , Ui(new Ui::MainWindow){

    Ui->setupUi(this);
    this->setWindowTitle("ROMapp");
    QPixmap Background(QDir().absoluteFilePath("../ROMapp/fig/background.jpg"));
    //Background = Background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette Palette;
    Palette.setBrush(QPalette::Background, Background);
    this->setPalette(Palette);
    //QPoint LeftTop = Ui->MapAxes->mapToGlobal(Ui->MapAxes->rect().topLeft());
    //QPoint RightBottom = Ui->MapAxes->mapToGlobal(Ui->MapAxes->rect().bottomRight());
    //QRect Cut(LeftTop.x(), LeftTop.y(),RightBottom.x()-LeftTop.x(),RightBottom.y()-LeftTop.y());
    QRect Cut(40, 90, 521, 651);
    Background = Background.copy(Cut);
    Ui->MapAxes->setBackground(Background);
    Ui->MapAxes->xAxis->setRange(-212.11,246.58);
    Ui->MapAxes->yAxis->setRange(-288.05,310.966);
    Ui->MapAxes->xAxis->grid()->setSubGridVisible(true);
    Ui->MapAxes->xAxis->grid()->setPen(QPen(QColor(10,10,10,170),1,Qt::DotLine));
    Ui->MapAxes->yAxis->grid()->setPen(QPen(QColor(10,10,10,170),1,Qt::DotLine));
    Ui->MapAxes->xAxis->grid()->setSubGridPen(QPen(QColor(50,50,50,170),0.5,Qt::DotLine));
    Ui->MapAxes->yAxis->grid()->setSubGridPen(QPen(QColor(50,50,50,170),0.5,Qt::DotLine));
    Ui->MapAxes->yAxis->grid()->setSubGridVisible(true);

    Ui->MapAxes->xAxis->setLabel("X [cm]");
    Ui->MapAxes->yAxis->setLabel("Y [cm]");
    Ui->MapAxes->plotLayout()->setMinimumMargins(QMargins(0,0,0,0));
    Ui->MapAxes->plotLayout()->setMargins(QMargins(0,0,0,0));
    Ui->MapAxes->yAxis->setPadding(0);
    Ui->MapAxes->yAxis->setLabelPadding(0);
    Ui->MapAxes->yAxis->setTickLabelPadding(1);
    Ui->MapAxes->yAxis->setOffset(0);
    Ui->MapAxes->yAxis2->setPadding(0);
    Ui->MapAxes->yAxis2->setLabelPadding(0);
    Ui->MapAxes->yAxis2->setTickLabelPadding(2);
    Ui->MapAxes->xAxis->setLabelPadding(0);
    Ui->MapAxes->xAxis->setTickLabelPadding(0);

    DatPlot = new DataForPlot;
    Ui->GraphsW->PlotInit(DatPlot);
    DataForDataTable Data;
    Ui->DataTableW->UpdateDisplay(Data);

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
    connect(TimMap, &QTimer::timeout, Ui->DataTableW, &DataTable::UpdateGraphics);
    Ui->PositionX->setReadOnly(true);
    Ui->PositionY->setReadOnly(true);
    Ui->PositionX->setAlignment(Qt::AlignRight);
    Ui->PositionY->setAlignment(Qt::AlignRight);
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
    Ui->DataTableW->UpdateDisplay();
    Ui->PositionX->setText(QString::number(CurrData.GetPosition(0), 'f', 2));
    Ui->PositionY->setText(QString::number(CurrData.GetPosition(1), 'f', 2));
}

void MainWindow::RefreshPlots(){
    Ui->GraphsW->RefreshPlots(CurrData);
}

void MainWindow::RefreshData(){
    CurrData = ThreadComm->ReadData();
    Ui->DataTableW->UpdateData(CurrData);
}

void MainWindow::RefreshMap(){
    Ui->MapW->AddPoint(CurrData.GetPosition(0), CurrData.GetPosition(1));
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
