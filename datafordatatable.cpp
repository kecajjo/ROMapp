#include "datafordatatable.h"

DataForDataTable::DataForDataTable(){
    Gyro = 0;
    Compass = 0;
    for(int i=0;i<2;i++){
        Position[i] = 0;
        PWM[i] = 0;
        Encoder[i] = 0;
    }
}

void DataForDataTable::SetPosition(const double *Tab){
    Position[0] = Tab[0];
    Position[1] = Tab[1];
}

void DataForDataTable::SetPosition(double const &X, double const &Y){
    Position[0] = X;
    Position[1] = Y;
}

void DataForDataTable::SetPWM(const double *Tab){
    PWM[0] = Tab[0];
    PWM[1] = Tab[1];
}

void DataForDataTable::SetPWM(double const &A, double const &B){
    PWM[0] = A;
    PWM[1] = B;
}

void DataForDataTable::SetEncoder(const double *Tab){
    Encoder[0] = Tab[0];
    Encoder[1] = Tab[1];
}

void DataForDataTable::SetEncoder(double const &A, double const &B){
    Encoder[0] = A;
    Encoder[1] = B;
}

void DataForDataTable::operator = (DataForDataTable const Dat){
    for(int i=0;i<2;i++){
        Position[i] = Dat.GetPosition(i);
        PWM[i] = Dat.GetPWM(i);
        Encoder[i] = Dat.GetEncoder(i);
    }
    Gyro = Dat.GetGyro();
    Compass = Dat.GetCompass();
}

std::istream& operator >> (std::istream& Stream, DataForDataTable &Data){
    double tab[2];
    Stream >> tab[0] >> tab[1];
    Data.SetPWM(tab);
    Stream >> tab[0] >> tab[1];
    Data.SetEncoder(tab);
    Stream >> tab[0] >> tab[1];
    Data.SetGyro(tab[0]);
    Data.SetCompass(tab[1]);

    return Stream;
}
