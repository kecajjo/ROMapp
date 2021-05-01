#include "programlogiceventloop.h"

void ProgramLogicEventLoop(Communication *Comm){
    DataTransform ConvertedData;
    DataFromSTM Test;
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
        usleep(100);
        i = (i+1)%1000;
    }
}
