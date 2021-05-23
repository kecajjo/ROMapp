#include "bluetoothwidget.h"
#include "ui_bluetoothwidget.h"

BluetoothWidget::BluetoothWidget(QWidget *parent) :
    QWidget(parent),
    Ui(new Ui::BluetoothWidget)
{
    Ui->setupUi(this);
}

BluetoothWidget::~BluetoothWidget()
{
    delete Ui;
}

void BluetoothWidget::Init(Communication *ThreadComm){
        this->ThreadComm = ThreadComm;
}

void BluetoothWidget::ConnectButtonClicked(){
    int Idx = Ui->DevicesBox->currentIndex();
    ThreadComm->ConnectToDeviceCommand(Idx);
}

void BluetoothWidget::RefreshDevBox(){
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

void BluetoothWidget::InitDevBox(){
    Ui->DevicesBox->setMaxVisibleItems(5);
}
