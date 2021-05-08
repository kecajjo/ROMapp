#ifndef DATATRANSFORM_H
#define DATATRANSFORM_H

#include "datafordatatable.h"
#include "datafromstm.h"

#include <vector>
#include <fstream>
#include <cstdlib>

#define SAMPLES 100

class DataTransform{
public:
    DataTransform();

    /*!
     * \brief ReadExampleData
     * function for testing program only
     */
    void ReadExampleData();

    DataForDataTable GetData() const {return CurrData;}
    void CalculateData(DataFromSTM DataToConvert);
    /*
     * \brief CalcPosition
     * \param X - previous position X axis, needed to determine current position
     * \param Y - previous position Y axis, needed to determine current position
     * \param Angle - previous angle in degree from north clockwise, needed to determine position
     *
     * Calculates position basing on sensors values and given position and angle
     * Updates current Position
     */
    //void CalcPosition(double const &X, double const &Y, double const &Angle);

private:
    /*!
     * \brief CalcPosition
     *
     * Calculates position basing on sensors values and previous position
     * Updates current Position
     */
    void CalcPosition();

private:
    std::vector<DataForDataTable> ExampleData;
    int CurrDataSample;
    DataForDataTable CurrData;
    double PrevPos[2];
    double PrevAngle;
};

/*!
 * \brief GenerateExampleData
 * function for testing program only
 */
void GenerateExampleData();
/*!
 * \brief fRand
 * function for testing program only
 */
double fRand(double fMin, double fMax);


#endif // DATATRANSFORM_H
