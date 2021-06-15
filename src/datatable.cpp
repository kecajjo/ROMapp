#include "datatable.h"
#include "ui_datatable.h"

DataTable::DataTable(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataTable){

    Data = new DataForDataTable;

    ui->setupUi(this);
    ui->PositionName->setText("Position:");
    ui->PWMName->setText("PWM:");
    ui->EncoderName->setText("Speed:");
    ui->GyroName->setText("Gyro:");
    ui->CompassName->setText("Compass:");
    ui->Degree->setText("°");
    ui->DegreePerSec->setText("°/s");
    ui->PositionX->setReadOnly(true);
    ui->PositionY->setReadOnly(true);
    ui->PWMA->setReadOnly(true);
    ui->PWMB->setReadOnly(true);
    ui->EncoderA->setReadOnly(true);
    ui->EncoderB->setReadOnly(true);
    ui->GyroData->setReadOnly(true);
    ui->CompassData->setReadOnly(true);


    UpdateDisplay();
}

DataTable::~DataTable()
{
    delete ui;
    delete Data;
}

void DataTable::UpdateDisplay(){
    ui->PositionX->setText(QString::number(Data->GetPosition(0), 'f', 2));
    ui->PositionY->setText(QString::number(Data->GetPosition(1), 'f', 2));
    ui->PWMA->setText(QString::number(Data->GetPWM(0), 'f', 2));
    ui->PWMB->setText(QString::number(Data->GetPWM(1), 'f', 2));
    ui->EncoderA->setText(QString::number(Data->GetEncoder(0), 'f', 2));
    ui->EncoderB->setText(QString::number(Data->GetEncoder(1), 'f', 2));
    ui->GyroData->setText(QString::number(Data->GetGyro(), 'f', 2));
    ui->CompassData->setText(QString::number(Data->GetCompass(), 'f', 2));
}

void DataTable::UpdateDisplay(DataForDataTable const Dat){
    *Data = Dat;
    ui->PositionX->setText(QString::number(Data->GetPosition(0), 'f', 2));
    ui->PositionY->setText(QString::number(Data->GetPosition(1), 'f', 2));
    ui->PWMA->setText(QString::number(Data->GetPWM(0), 'f', 2));
    ui->PWMB->setText(QString::number(Data->GetPWM(1), 'f', 2));
    ui->EncoderA->setText(QString::number(Data->GetEncoder(0), 'f', 2));
    ui->EncoderB->setText(QString::number(Data->GetEncoder(1), 'f', 2));
    ui->GyroData->setText(QString::number(Data->GetGyro(), 'f', 2));
    ui->CompassData->setText(QString::number(Data->GetCompass(), 'f', 2));
}

void DataTable::UpdateData(DataForDataTable const dat){
    *Data = dat;
}
