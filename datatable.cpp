#include "datatable.h"
#include "ui_datatable.h"

DataTable::DataTable(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataTable){

    Data = new DataForDataTable;

    ui->setupUi(this);
    ui->PositionName->setText("Position:");
    ui->PWMName->setText("PWM:");
    ui->EncoderName->setText("Encoders:");
    ui->GyroName->setText("Gyro:");
    ui->CompassName->setText("Compass:");

    UpdateDisplay();
}

DataTable::~DataTable()
{
    delete ui;
    delete Data;
}

void DataTable::UpdateDisplay(){
    ui->PositionX->setText("X: " + QString::number(Data->GetPosition(0)));
    ui->PositionY->setText("Y: " + QString::number(Data->GetPosition(1)));
    ui->PWMA->setText("A: " + QString::number(Data->GetPWM(0)));
    ui->PWMB->setText("B: " + QString::number(Data->GetPWM(1)));
    ui->EncoderA->setText("A: " + QString::number(Data->GetEncoder(0)));
    ui->EncoderB->setText("B: " + QString::number(Data->GetEncoder(1)));
    ui->GyroData->setText(QString::number(Data->GetGyro()));
    ui->CompassData->setText(QString::number(Data->GetCompass()));
}

void DataTable::UpdateDisplay(DataForDataTable const Dat){
    *Data = Dat;
    ui->PositionX->setText("X: " + QString::number(Data->GetPosition(0)));
    ui->PositionY->setText("Y: " + QString::number(Data->GetPosition(1)));
    ui->PWMA->setText("A: " + QString::number(Data->GetPWM(0)));
    ui->PWMB->setText("B: " + QString::number(Data->GetPWM(1)));
    ui->EncoderA->setText("A: " + QString::number(Data->GetEncoder(0)));
    ui->EncoderB->setText("B: " + QString::number(Data->GetEncoder(1)));
    ui->GyroData->setText(QString::number(Data->GetGyro()));
    ui->CompassData->setText(QString::number(Data->GetCompass()));
}

void DataTable::UpdateData(DataForDataTable const dat){
    *Data = dat;
}
