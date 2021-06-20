#include "datatable.h"
#include "ui_datatable.h"

DataTable::DataTable(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataTable){

    ui->setupUi(this);
    Data = new DataForDataTable;
    EncodersBarOverZero = new QCPBars(ui->Graph->xAxis, ui->Graph->yAxis);
    EncodersBarBelowZero = new QCPBars(ui->Graph->xAxis, ui->Graph->yAxis);
    PWMBar = new QCPBars(ui->Graph->xAxis, ui->Graph->yAxis2);

    InitPlots();

    ui->PWMName->setText("PWM:");
    ui->EncoderName->setText("Speed:");
    ui->GyroName->setText("Gyro:");
    ui->CompassName->setText("Compass:");
    ui->HeadingName->setText("Heading:");
    ui->Degree->setText("°");
    ui->Degree2->setText("°");
    ui->DegreePerSec->setText("°/s");
    ui->PWMA->setReadOnly(true);
    ui->PWMB->setReadOnly(true);
    ui->EncoderA->setReadOnly(true);
    ui->EncoderB->setReadOnly(true);
    ui->GyroData->setReadOnly(true);
    ui->CompassData->setReadOnly(true);
    ui->HeadingData->setReadOnly(true);
    ui->PWMA->setAlignment(Qt::AlignRight);
    ui->PWMB->setAlignment(Qt::AlignRight);
    ui->EncoderA->setAlignment(Qt::AlignRight);
    ui->EncoderB->setAlignment(Qt::AlignRight);
    ui->GyroData->setAlignment(Qt::AlignRight);
    ui->CompassData->setAlignment(Qt::AlignRight);
    ui->HeadingData->setAlignment(Qt::AlignRight);

    WindRoseImg.load(QDir().absoluteFilePath("../ROMapp/fig/wind_rose.png"));

    ui->WindRose->setAlignment(Qt::AlignCenter);
    ui->Arrow->setScaledContents(true);
    Arrow.load(QDir().absoluteFilePath("../ROMapp/fig/arrow.png"));
    ui->Arrow->setPixmap(Arrow);

    UpdateDisplay();
}

DataTable::~DataTable()
{
    delete Data;
    delete ui;
}

void DataTable::UpdateDisplay(){
    ui->PWMA->setText(QString::number(Data->GetPWM(0), 'f', 2));
    ui->PWMB->setText(QString::number(Data->GetPWM(1), 'f', 2));
    ui->EncoderA->setText(QString::number(Data->GetEncoder(0), 'f', 2));
    ui->EncoderB->setText(QString::number(Data->GetEncoder(1), 'f', 2));
    ui->GyroData->setText(QString::number(Data->GetGyro(), 'f', 2));
    ui->CompassData->setText(QString::number(Data->GetCompass(), 'f', 2));
    ui->HeadingData->setText(QString::number(Data->GetHeading(), 'f', 2));

    QVector<double> TicksForPWM, TicksForEncoders;
    TicksForPWM << 0.5+0.03+0.25/2 << 1.5+0.03+0.25/2;
    TicksForEncoders << 0.5-0.03-0.25/2 << 1.5-0.03-0.25/2;

    QVector<double> EncoderDataOverZero(2), EncoderDataBelowZero(2), PWMData(2);
    for(int i=0;i<2;i++){
        if(Data->GetEncoder(i) > 0){
            EncoderDataBelowZero[i] = 0;
            EncoderDataOverZero[i] = Data->GetEncoder(i);
        } else{
            EncoderDataBelowZero[i] = -1*Data->GetEncoder(i);
            EncoderDataOverZero[i] = 0;
        }
        PWMData[i] = Data->GetPWM(i);
    }
    EncodersBarOverZero->setData(TicksForEncoders, EncoderDataOverZero);
    EncodersBarBelowZero->setData(TicksForEncoders, EncoderDataBelowZero);
    PWMBar->setData(TicksForPWM, PWMData);
    ui->Graph->replot();
}

void DataTable::UpdateDisplay(DataForDataTable const Dat){
    *Data = Dat;
    ui->PWMA->setText(QString::number(Data->GetPWM(0), 'f', 2));
    ui->PWMB->setText(QString::number(Data->GetPWM(1), 'f', 2));
    ui->EncoderA->setText(QString::number(Data->GetEncoder(0), 'f', 2));
    ui->EncoderB->setText(QString::number(Data->GetEncoder(1), 'f', 2));
    ui->GyroData->setText(QString::number(Data->GetGyro(), 'f', 2));
    ui->CompassData->setText(QString::number(Data->GetCompass(), 'f', 2));
    ui->HeadingData->setText(QString::number(Data->GetHeading(), 'f', 2));

    QVector<double> TicksForPWM, TicksForEncoders;
    TicksForPWM << 0.5+0.03+0.25/2 << 1.5+0.03+0.25/2;
    TicksForEncoders << 0.5-0.03-0.25/2 << 1.5-0.03-0.25/2;

    QVector<double> EncoderDataOverZero(2), EncoderDataBelowZero(2), PWMData(2);
    for(int i=0;i<2;i++){
        if(Data->GetEncoder(i) > 0){
            EncoderDataBelowZero[i] = 0;
            EncoderDataOverZero[i] = Data->GetEncoder(i);
        } else{
            EncoderDataBelowZero[i] = Data->GetEncoder(i);
            EncoderDataOverZero[i] = 0;
        }
        PWMData[i] = Data->GetPWM(i);
    }
    EncodersBarOverZero->setData(TicksForEncoders, EncoderDataOverZero);
    EncodersBarBelowZero->setData(TicksForEncoders, EncoderDataBelowZero);
    PWMBar->setData(TicksForPWM, PWMData);
    ui->Graph->replot();
}

void DataTable::UpdateGraphics(){
    RotateWindRose();
}

void DataTable::UpdateData(DataForDataTable const Dat){
    *Data = Dat;
}

void DataTable::RotateWindRose(){
    QTransform Rot;
    QPixmap Tmp = WindRoseImg.scaled(ui->WindRose->width(), ui->WindRose->height());
    Rot.rotate(-1*Data->GetHeading());
    Tmp = Tmp.transformed(Rot);
    ui->WindRose->setPixmap(Tmp);
}

void DataTable::InitPlots(){

    EncodersBarOverZero->setWidth(0.25);
    EncodersBarBelowZero->setWidth(0.25);
    PWMBar->setWidth(0.25);
    EncodersBarOverZero->setPen(QPen(QColor(50, 200, 50, 255)));
    EncodersBarOverZero->setBrush(QBrush(QColor(50, 200, 50, 80)));
    EncodersBarBelowZero->setPen(QPen(QColor(200, 50, 50, 255)));
    EncodersBarBelowZero->setBrush(QBrush(QColor(200, 50, 50, 80)));
    PWMBar->setPen(QPen(QColor(50, 50, 200, 255)));
    PWMBar->setBrush(QBrush(QColor(50, 50, 200, 80)));
    EncodersBarOverZero->setName("Moving forward");
    EncodersBarBelowZero->setName("Moving backward");
    PWMBar->setName("PWM");

    //QCPBarsGroup *BarGroup = new QCPBarsGroup(ui->Graph);
    //BarGroup->append(EncodersBarOverZero);
    //BarGroup->append(PWMBar);
    QVector<double> TicksForPWM, TicksForEncoders;
    QVector<QString> Labels;
    TicksForPWM << 0.5+0.03+0.25/2 << 1.5+0.03+0.25/2;
    TicksForEncoders << 0.5-0.03-0.25/2 << 1.5-0.03-0.25/2;
    Labels << "Left" << "Right";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(TicksForEncoders, Labels);
    ui->Graph->xAxis->setTicker(textTicker);
    ui->Graph->xAxis->setTickLabelRotation(60);
    ui->Graph->xAxis->setSubTicks(false);
    ui->Graph->yAxis->setRange(0, 15);
    ui->Graph->yAxis2->setRange(0, 100);
    ui->Graph->yAxis2->setVisible(true);
    ui->Graph->yAxis->setLabel("Wheel Speed");
    ui->Graph->yAxis2->setLabel("PWM");
    ui->Graph->xAxis->setRange(0, 2);
    ui->Graph->xAxis->grid()->setVisible(false);
    ui->Graph->xAxis->setTickLengthIn(0);
    ui->Graph->plotLayout()->setColumnSpacing(1);

    ui->Graph->plotLayout()->setMinimumMargins(QMargins(0,0,0,0));
    ui->Graph->plotLayout()->setMargins(QMargins(0,0,0,0));
    ui->Graph->yAxis->setPadding(0);
    ui->Graph->yAxis->setLabelPadding(0);
    ui->Graph->yAxis->setTickLabelPadding(1);
    ui->Graph->yAxis->setOffset(0);
    ui->Graph->yAxis2->setPadding(0);
    ui->Graph->yAxis2->setLabelPadding(0);
    ui->Graph->yAxis2->setTickLabelPadding(2);
    ui->Graph->xAxis->setLabelPadding(0);
    ui->Graph->xAxis->setTickLabelPadding(0);
    ui->Graph->yAxis2->setOffset(0);
    ui->Graph->legend->setVisible(true);
    ui->Graph->plotLayout()->setRowSpacing(0);
    ui->Graph->yAxis->grid()->setPen(QPen(QColor(20,20,20,255),1,Qt::DotLine));
    ui->Graph->yAxis2->grid()->setPen(QPen(QColor(20,20,20,255),1,Qt::DotLine));


    QPixmap Background(QDir().absoluteFilePath("../ROMapp/fig/background.jpg"));
    QRect Cut(597,500,811,800);
    Background = Background.copy(Cut);
    ui->Graph->setBackground(Background);

    ui->Graph->plotLayout()->insertRow(0);
    ui->Graph->plotLayout()->addElement(0, 0, new QCPTextElement(ui->Graph, "Wheel speed\nand PWM values", QFont("sans", 10, QFont::Bold)));

    ui->Graph->plotLayout()->insertRow(2);
    ui->Graph->plotLayout()->addElement(2, 0, ui->Graph->legend);
    ui->Graph->plotLayout()->setRowStretchFactor(2, 0.0001);
    ui->Graph->legend->setBrush(QColor(255,255,255,0));
    ui->Graph->legend->setBorderPen(QColor(255,255,255,0));
    ui->Graph->legend->setMinimumMargins(QMargins(0,0,0,0));
    ui->Graph->legend->setMargins(QMargins(0,0,0,0));
    ui->Graph->legend->setIconTextPadding(0);

    QVector<double> EncoderDataOverZero, EncoderDataBelowZero, PWMData;
    EncoderDataOverZero << 6 << 0;
    EncoderDataBelowZero << 0 << 12;
    PWMData << 50 << 90;
    EncodersBarOverZero->setData(TicksForEncoders, EncoderDataOverZero);
    EncodersBarBelowZero->setData(TicksForEncoders, EncoderDataBelowZero);
    PWMBar->setData(TicksForPWM, PWMData);

}
