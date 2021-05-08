#include "datatransform.h"

DataTransform::DataTransform(){
    GenerateExampleData();
    ReadExampleData();
    CurrDataSample = 0;
}

void DataTransform::ReadExampleData(){
    std::ifstream F("ExDat.txt");
    DataForDataTable Dat;
    int i = 0;
    while(F >> Dat){
        if(i==0){
            PrevPos[0] = 0;
            PrevPos[1] = 0;
        }
        CurrData = Dat;
        ExampleData.push_back(CurrData);
        ++i;
    }
    F.close();
}

void DataTransform::CalculateData(DataFromSTM DataToConvert){
    CurrData = ExampleData[CurrDataSample];
    CurrDataSample = (CurrDataSample+1)%SAMPLES;
    CalcPosition();
    PrevPos[0] = CurrData.GetPosition(0);
    PrevPos[1] = CurrData.GetPosition(1);
    PrevAngle = 0;
}

void DataTransform::CalcPosition(){
    double X = CurrData.GetEncoder(0) + PrevPos[0];
    double Y = CurrData.GetEncoder(1) + PrevPos[1];
    CurrData.SetPosition(X, Y);
}
/*
void DataTransform::CalcPosition(double const &X, double const &Y, double const &Angle){
    Position[0] = Encoder[0] + X;
    Position[1] = Encoder[1] + Y;
}
*/
void GenerateExampleData(){
    std::ofstream F("ExDat.txt");
    srand (time(NULL));
    double tab[6];
    for(int i=0;i<100;i++){
        tab[0] = fRand(0.01, 99.8);
        tab[1] = fRand(0.01, 99.8);
        tab[2] = fRand(0.01, 2.03);
        tab[3] = fRand(0.01, 2.03);
        tab[4] = fRand(0.01, 119.8);
        tab[5] = fRand(0.01, 359.8);
        for(int j=0;j<6;j++){
            F << tab[j] << " ";
        }
        F << std::endl;
    }
    F.close();
}
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
