#ifndef DATAFORDATATABLE_H
#define DATAFORDATATABLE_H

#include <iostream>

class DataForDataTable{
    double Position[2];
    double PWM[2];
    double Encoder[2];
    double Gyro;
    double Compass;
public:
    DataForDataTable();
    //~DataForDataTable();
    void SetPosition(double const *tab);
    const double* GetPtrPosition() const {return Position;}
    double GetPosition (int index) const {return Position[index];}
    void SetPWM(double const *tab);
    void SetPWM(double const A, double const B);
    const double* GetPtrPWM() const {return PWM;}
    double GetPWM(int index) const {return PWM[index];}
    void SetEncoder(double const *tab);
    void SetEncoder(double const A, double const B);
    const double* GetPtrEncoder() const {return Encoder;}
    double GetEncoder(int index) const {return Encoder[index];}
    void SetGyro(double const val){Gyro = val;}
    double GetGyro() const {return Gyro;}
    void SetCompass(double const val){Compass = val;}
    double GetCompass() const {return Compass;}
    void operator = (DataForDataTable const dat);
    /*
     * Input:
     * PrevPosition - 2 element array, previous position, needed to determine current position
     *
     * Calculates position basing on sensors values
     * Updates current Position
    */
    void CalcPosition(double const *PrevPosition);
    /*
     * Input:
     * x - previous position X axis, needed to determine current position
     * y - previous position Y axis, needed to determine current position
     *
     * Calculates position basing on sensors values
     * Updates current Position
    */
    void CalcPosition(double const X, double const Y);
};


/*
 * NOTE: after reading DataForDataTable it is necesarry to use CalcPosition function
 * to update Positions value
*/
std::istream& operator >> (std::istream& Stream, DataForDataTable &data);

#endif // DATAFORDATATABLE_H
