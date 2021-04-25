#include "datatable.h"
#include "ui_datatable.h"

DataTable::DataTable(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataTable){

    data = new DataForDataTable;

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
    delete data;
}

void DataTable::UpdateDisplay(){
    ui->PositionX->setText("X: " + QString::number(data->GetPosition(0)));
    ui->PositionY->setText("Y: " + QString::number(data->GetPosition(1)));
    ui->PWMA->setText("A: " + QString::number(data->GetPWM(0)));
    ui->PWMB->setText("B: " + QString::number(data->GetPWM(1)));
    ui->EncoderA->setText("A: " + QString::number(data->GetEncoder(0)));
    ui->EncoderB->setText("B: " + QString::number(data->GetEncoder(1)));
    ui->GyroData->setText(QString::number(data->GetGyro()));
    ui->CompassData->setText(QString::number(data->GetCompass()));
}

void DataTable::UpdateDisplay(DataForDataTable const Dat){
    *data = Dat;
    ui->PositionX->setText("X: " + QString::number(data->GetPosition(0)));
    ui->PositionY->setText("Y: " + QString::number(data->GetPosition(1)));
    ui->PWMA->setText("A: " + QString::number(data->GetPWM(0)));
    ui->PWMB->setText("B: " + QString::number(data->GetPWM(1)));
    ui->EncoderA->setText("A: " + QString::number(data->GetEncoder(0)));
    ui->EncoderB->setText("B: " + QString::number(data->GetEncoder(1)));
    ui->GyroData->setText(QString::number(data->GetGyro()));
    ui->CompassData->setText(QString::number(data->GetCompass()));
}

void DataTable::UpdateData(DataForDataTable const dat){
    *data = dat;
}
