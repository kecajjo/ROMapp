#ifndef DATATRANSFORM_H
#define DATATRANSFORM_H

#include "datafordatatable.h"
#include "datafromstm.h"

#include <QByteArray>
#include <fstream>
#include <cstdlib>
#include <math.h>

#define MAX_PWM 6400
#define ENCODER_PER_ROTATION 11132//506*11*2
#define WHEEL_DIAMETER 67//in millimeters
#define MAX_GYRO 32767
#define GYRO_RANGE 250

/*!
 * \brief The DataTransform class
 * Helps in transforming data from raw bytes to DataForDataTable format.
 * Calculates the robot position.
 */
class DataTransform{
public:
    /*!
     * \brief DataTransform
     * Default constructor.
     */
    DataTransform();

    /*!
     * \brief GetData
     * \return data stored in class
     */
    DataForDataTable GetData() const {return CurrData;}
    /*!
     * \brief CalculateData
     * \param[in] RawData - raw data to be transformed
     * Calculates position and transforms raw data to DataForDataTable format.
     *
     * NOTE: if RawData size isn't 14, returns without any calculations.
     */
    void CalculateData(QByteArray *RawData);

private:
    /*!
     * \brief CalcPosition
     *
     * Calculates position basing on sensors values and previous position and angle.
     * Updates current Position.
     */
    void CalcPosition();

private:
    /*!
     * \brief CurrData
     *  Current data, already transformed from the raw values.
     */
    DataForDataTable CurrData;
    /*!
     * \brief PrevPos
     * Previous robot position in cm.
     * [0] - X axis
     * [1] - Y axis
     */
    double PrevPos[2];
    /*!
     * \brief PrevAngle
     * Previous robot heading in degree.
     * 0 - facing north
     */
    double PrevAngle;
};


#endif // DATATRANSFORM_H
