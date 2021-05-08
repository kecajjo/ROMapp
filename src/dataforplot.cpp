#include "dataforplot.h"

DataForPlot::DataForPlot(){
    XAxisGraphVal.resize(SAMPLES);
    PWMA.resize(SAMPLES);
    PWMB.resize(SAMPLES);
    EncoderA.resize(SAMPLES);
    EncoderB.resize(SAMPLES);
    Gyro.resize(SAMPLES);
    Compass.resize(SAMPLES);
}

DataForPlot::~DataForPlot(){
    XAxisGraphVal.clear();
    PWMA.clear();
    PWMB.clear();
    EncoderA.clear();
    EncoderB.clear();
    Gyro.clear();
    Compass.clear();
}
