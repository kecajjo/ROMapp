#ifndef DATAFORPLOT_H
#define DATAFORPLOT_H

#include <QVector>

#define SAMPLES 400
/*!
  * \brief DataForPlot
  * struct cointaining QVectors for plotting PWM, Encoders, Gyro and Compass values
  */
typedef struct DataForPlot{
    /*!
     * \brief XAxisGraphVal
     * Values on time axis
     */
    QVector<double> XAxisGraphVal;
    /*!
     * \brief PWMA
     * Historic values of left motor PWM
     * in %
     */
    QVector<double> PWMA;
    /*!
     * \brief PWMB
     * Historc values of right motor PWM
     * in %
     */
    QVector<double> PWMB;
    /*!
     * \brief EncoderA
     * Historic values of left motor speed
     * in cm/s
     */
    QVector<double> EncoderA;
    /*!
     * \brief EncoderB
     * Historic values of right motor speed
     * in cm/s
     */
    QVector<double> EncoderB;
    /*!
     * \brief Gyro
     * Historic values read from gyroscope
     * in dps
     */
    QVector<double> Gyro;
    /*!
     * \brief Compass
     * Historic values of robot headings
     * in degree
     */
    QVector<double> Compass;

    /*!
     * \brief DataForPlot
     * initializes all QVector of struct with SAMPLES elements
     */
    DataForPlot();
    ~DataForPlot();
} DataForPlot;

#endif // DATAFORPLOT_H
