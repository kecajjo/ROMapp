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
     * \param[in] tab - 2element array, it values will be copied to Position array
     */
    void SetPosition(double const *Tab);
    /*!
     * \brief SetPosition
     * \param[in] X - new value of Position[0]
     * \param[in] Y - new value of Position[1]
     */
    void SetPosition(double const &X, double const &Y);
    /*!
     * \brief GetPtrPosition
     * \return pointer to 2element array containing values of Position
     */
    const double* GetPtrPosition() const {return Position;}
    /*!
     * \brief GetPosition
     * \param[in] index - index of Position, must be 0 or 1
     * \return value of Position[index]
     */
    double GetPosition (int Index) const {return Position[Index];}
    /*!
     * \brief SetPWM
     * \param tab - 2element array, it values will be copied to PWM array
     */
    void SetPWM(double const *Tab);
    /*!
     * \brief SetPWM
     * \param[in] A - new value of PWM[0]
     * \param[in] B - new value of PWM[1]
     */
    void SetPWM(double const &A, double const &B);
    /*!
     * \brief GetPtrPWM
     * \return pointer to 2element array containing values of PWM
     */
    const double* GetPtrPWM() const {return PWM;}
    /*!
     * \brief GetPWM
     * \param[in] index - index of PWM, must be 0 or 1
     * \return value of PWM[index]
     */
    double GetPWM(int Index) const {return PWM[Index];}
    /*!
     * \brief SetEncoder
     * \param[in] tab - 2element array, it values will be copied to Encoder array
     */
    void SetEncoder(double const *Tab);
    /*!
     * \brief SetEncoder
     * \param[in] A - new value of encoder[0]
     * \param[in] B - new value of encoder[1]
     */
    void SetEncoder(double const &A, double const &B);
    /*!
     * \brief GetPtrEncoder
     * \return pointer to 2element array containing values of Encoders
     */
    const double* GetPtrEncoder() const {return Encoder;}
    /*!
     * \brief GetEncoder
     * \param[in] index - index of encoder, must be 0 or 1
     * \return value of encoder[index]
     */
    double GetEncoder(int Index) const {return Encoder[Index];}
    /*!
     * \brief SetGyro sets Gyro value
     * \param[in] val - new Gyro value
     */
    void SetGyro(double const &Val){Gyro = Val;}
    /*!
     * \brief GetGyro
     * \return Gyro value
     */
    double GetGyro() const {return Gyro;}
    /*!
     * \brief SetCompass sets Compass value
     * \param[in] val - new Compass value
     */
    void SetCompass(double const &Val){Compass = Val;}
    /*!
     * \brief GetCompass
     * \return Compass value
     */
    double GetCompass() const {return Compass;}

    /*!
     * \brief operator =
     * \param[in] Dat - value we assign
     * Overloaded operator =, assigns Dat to this datatable
     */
    void operator = (DataForDataTable const Dat);
};


/*!
 * \brief operator >>
 * \param[in/out] Stream - referance to stream from which we read data
 * \param[in] data - reference to data which we want to update
 * \return reference to the stream from which we read data
 *
 * NOTE: after reading DataForDataTable it is necesarry to use CalcPosition function
 * to update Positions value
*/
std::istream& operator >> (std::istream& Stream, DataForDataTable &Data);

#endif // DATAFORDATATABLE_H
