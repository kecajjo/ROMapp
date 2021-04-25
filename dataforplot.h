#ifndef DATAFORPLOT_H
#define DATAFORPLOT_H

#include <QVector>

#define SAMPLES 100

typedef struct DataForPlot{
    QVector<double> XAxisGraphVal;
    QVector<double> PWMA;
    QVector<double> PWMB;
    QVector<double> EncoderA;
    QVector<double> EncoderB;
    QVector<double> Gyro;
    QVector<double> Compass;

    DataForPlot();
    ~DataForPlot();
} DataForPlot;

#endif // DATAFORPLOT_H
