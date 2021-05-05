#include "programlogiceventloop.h"
#include <QDebug>

void ProgramLogicEventLoop(Communication *Comm){
    DataTransform ConvertedData;
    DataFromSTM Test;
    QBluetoothDeviceInfo *DevInfo;
    bool NewDataFromBT = true;
    int i=0;
    ConvertedData.ReadExampleData();
    while(!Comm->IsExitCommand()){
        if(i==0){
            if(NewDataFromBT == true){
                ConvertedData.CalculateData(Test);
                Comm->SendData(ConvertedData.GetData());
            }
        }
        if(Comm->IsScanCommand()){
            Comm->ClearScanCommand();
            qDebug() << "Scanning";
        }
        if(Comm->IsConnectCommand()){
            DevInfo = Comm->DeviceToConnectTo();
            qDebug() << "Connecting";
        }
        if(Comm->IsDisconnectCommand()){
            Comm->ClearDisconnectCommand();
            qDebug() << "Disconnecting";
        }
        usleep(100);
        i = (i+1)%1000;
    }
}
