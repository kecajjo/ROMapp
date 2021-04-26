#ifndef DATAFORDATATABLE_H
#define DATAFORDATATABLE_H

#include <iostream>

/*!
 * \brief The DataForDataTable class
 * Class containing all data used by DataTable
 */
class DataForDataTable{
    double Position[2];
    double PWM[2];
    double Encoder[2];
    double Gyro;
    double Compass;
public:
    /*!
     * \brief DataForDataTable
     * Contructor, initializes all class valiables with 0;
     */
    DataForDataTable();
    //~DataForDataTable();
    /*!
     * \brief SetPosition
     * \param tab - 2element array, it values will be copied to Position array
     */
    void SetPosition(double const *tab);
    /*!
     * \brief GetPtrPosition
     * \return pointer to 2element array containing values of Position
     */
    const double* GetPtrPosition() const {return Position;}
    /*!
     * \brief GetPosition
     * \param index - index of Position, must be 0 or 1
     * \return value of Position[index]
     */
    double GetPosition (int index) const {return Position[index];}
    /*!
     * \brief SetPWM
     * \param tab - 2element array, it values will be copied to PWM array
     */
    void SetPWM(double const *tab);
    /*!
     * \brief SetPWM
     * \param A - new value of PWM[0]
     * \param B - new value of PWM[1]
     */
    void SetPWM(double const A, double const B);
    /*!
     * \brief GetPtrPWM
     * \return pointer to 2element array containing values of PWM
     */
    const double* GetPtrPWM() const {return PWM;}
    /*!
     * \brief GetPWM
     * \param index - index of PWM, must be 0 or 1
     * \return value of PWM[index]
     */
    double GetPWM(int index) const {return PWM[index];}
    /*!
     * \brief SetEncoder
     * \param tab - 2element array, it values will be copied to Encoder array
     */
    void SetEncoder(double const *tab);
    /*!
     * \brief SetEncoder
     * \param A - new value of encoder[0]
     * \param B - new value of encoder[1]
     */
    void SetEncoder(double const A, double const B);
    /*!
     * \brief GetPtrEncoder
     * \return pointer to 2element array containing values of Encoders
     */
    const double* GetPtrEncoder() const {return Encoder;}
    /*!
     * \brief GetEncoder
     * \param index - index of encoder, must be 0 or 1
     * \return value of encoder[index]
     */
    double GetEncoder(int index) const {return Encoder[index];}
    /*!
     * \brief SetGyro sets Gyro value
     * \param val - new Gyro value
     */
    void SetGyro(double const val){Gyro = val;}
    /*!
     * \brief GetGyro
     * \return Gyro value
     */
    double GetGyro() const {return Gyro;}
    /*!
     * \brief SetCompass sets Compass value
     * \param val - new Compass value
     */
    void SetCompass(double const val){Compass = val;}
    /*!
     * \brief GetCompass
     * \return Compass value
     */
    double GetCompass() const {return Compass;}
    void operator = (DataForDataTable const dat);
    /*!
     * \brief CalcPosition
     * \param PrevPosition - 2 element array, previous position, needed to determine current position
     *
     * Calculates position basing on sensors values
     * Updates current Position
     */
    void CalcPosition(double const *PrevPosition);
    /*!
     * \brief CalcPosition
     * \param X - previous position X axis, needed to determine current position
     * \param Y - previous position Y axis, needed to determine current position
     *
     * Calculates position basing on sensors values
     * Updates current Position
     */
    void CalcPosition(double const X, double const Y);
};


/*!
 * \brief operator >>
 * \param Stream - referance to stream from which we read data
 * \param data - reference to data which we want to update
 * \return reference to the stream from which we read data
 *
 * NOTE: after reading DataForDataTable it is necesarry to use CalcPosition function
 * to update Positions value
*/
std::istream& operator >> (std::istream& Stream, DataForDataTable &data);

#endif // DATAFORDATATABLE_H
