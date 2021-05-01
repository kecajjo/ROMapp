#ifndef DATAFORPLOT_H
#define DATAFORPLOT_H

#include <QVector>

#define SAMPLES 400
/*!
  * \brief DataForPlot
  * struct cointaining QVectors for plotting PWM, Encoders, Gyro and Compass values
  */
typedef struct DataForPlot{
    QVector<double> XAxisGraphVal;
    QVector<double> PWMA;
    QVector<double> PWMB;
    QVector<double> EncoderA;
    QVector<double> EncoderB;
    QVector<double> Gyro;
    QVector<double> Compass;

    /*!
     * \brief DataForPlot
     * initializes all QVector of struct with SAMPLES elements
     */
    DataForPlot();
    /*!
      * \brief ~DataForPlot
      * clears all QVectors inisde struct
      */
    ~DataForPlot();
} DataForPlot;

#endif // DATAFORPLOT_H
