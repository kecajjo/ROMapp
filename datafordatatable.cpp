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

void DataForDataTable::SetPosition(const double *tab){
    Position[0] = tab[0];
    Position[1] = tab[1];
}

void DataForDataTable::SetPWM(const double *tab){
    PWM[0] = tab[0];
    PWM[1] = tab[1];
}

void DataForDataTable::SetPWM(double const A, double const B){
    PWM[0] = A;
    PWM[1] = B;
}

void DataForDataTable::SetEncoder(const double *tab){
    Encoder[0] = tab[0];
    Encoder[1] = tab[1];
}

void DataForDataTable::SetEncoder(double const A, double const B){
    Encoder[0] = A;
    Encoder[1] = B;
}

void DataForDataTable::operator = (DataForDataTable const dat){
    for(int i=0;i<2;i++){
        Position[i] = dat.GetPosition(i);
        PWM[i] = dat.GetPWM(i);
        Encoder[i] = dat.GetEncoder(i);
    }
    Gyro = dat.GetGyro();
    Compass = dat.GetCompass();
}

void DataForDataTable::CalcPosition(double const *PrevPosition){
    Position[0] = Encoder[0] + PrevPosition[0];
    Position[1] = Encoder[1] + PrevPosition[1];
}

void DataForDataTable::CalcPosition(double const X, double const Y){
    Position[0] = Encoder[0] + X;
    Position[1] = Encoder[1] + Y;
}

std::istream& operator >> (std::istream& Stream, DataForDataTable &data){
    double tab[2];
    Stream >> tab[0] >> tab[1];
    data.SetPWM(tab);
    Stream >> tab[0] >> tab[1];
    data.SetEncoder(tab);
    Stream >> tab[0] >> tab[1];
    data.SetGyro(tab[0]);
    data.SetCompass(tab[1]);

    return Stream;
}
