#include "datatransform.h"
#include <QDebug>
DataTransform::DataTransform(){
}

void DataTransform::CalculateData(QByteArray *RawData){

    if(RawData->length() != 14) return;

    Uint8ToFloat RawToCompass;
    Uint8ToUint RawToPWMA, RawToPWMB;
    Uint8ToInt RawToEncoderA, RawToEncoderB, RawToGyro;

    int LE = 1;
    if(*(char *)&LE == 1){//if Little-Endian
        for(int i=0;i<2;i++){
            RawToPWMA.Uint8[i] = (*RawData)[i];
            RawToPWMB.Uint8[i] = (*RawData)[i+2];
            RawToEncoderA.Uint8[i] = (*RawData)[i+4];
            RawToEncoderB.Uint8[i] = (*RawData)[i+6];
            RawToGyro.Uint8[i] = (*RawData)[i+8];
        }
        for(int i=0;i<4;i++){
            RawToCompass.Uint8[i] = (*RawData)[i+10];
        }
    }else{//Big-Endian
        for(int i=0;i<2;i++){
            RawToPWMA.Uint8[i] = (*RawData)[1-i];
            RawToPWMB.Uint8[i] = (*RawData)[3-i];
            RawToEncoderA.Uint8[i] = (*RawData)[5-i];
            RawToEncoderB.Uint8[i] = (*RawData)[7-i];
            RawToGyro.Uint8[i] = (*RawData)[9-i];
        }
        for(int i=0;i<4;i++){
            RawToCompass.Uint8[i] = (*RawData)[13-i];
        }
    }

    float PWMA, PWMB, EncoderA, EncoderB, Gyro, Compass;

    PWMA = (double)(RawToPWMA.Uint)/MAX_PWM*100;
    PWMB = (double)(RawToPWMB.Uint)/MAX_PWM*100;
    EncoderA = double(RawToEncoderA.I)*M_PI*WHEEL_DIAMETER/ENCODER_PER_ROTATION*2;//10samples per second value in cm/sec
    EncoderB = double(RawToEncoderB.I)*M_PI*WHEEL_DIAMETER/ENCODER_PER_ROTATION*2;//10samples per second value in cm/sec
    Gyro = -1*(double)(RawToGyro.I)*GYRO_RANGE/MAX_GYRO;
    Compass = RawToCompass.F;//*180/M_PI;

    CurrData.SetPWM(PWMA, PWMB);
    CurrData.SetEncoder(EncoderA, EncoderB);
    CurrData.SetGyro(Gyro);
    CurrData.SetCompass(Compass);
    double Heading = 0.97*(CurrData.GetHeading() + Gyro/10) + 0.03*Compass;//10samples per sec
    //normalizing heading value
    if(Heading > 180) Heading -= 360;
    if(Heading < -180) Heading += 360;
    CurrData.SetHeading(Heading);
    CalcPosition();
    PrevPos[0] = CurrData.GetPosition(0);
    PrevPos[1] = CurrData.GetPosition(1);
    PrevAngle = Compass;
}

void DataTransform::CalcPosition(){
    //0 degree angle facing north, Y axis facing north, X axis facing east
    //Position in centimeters
    double X = sin(CurrData.GetHeading()*M_PI/180)*(CurrData.GetEncoder(0)+CurrData.GetEncoder(1))/20 + PrevPos[0];
    double Y = cos(CurrData.GetHeading()*M_PI/180)*(CurrData.GetEncoder(0)+CurrData.GetEncoder(1))/20 + PrevPos[1];
    CurrData.SetPosition(X, Y);
}
/*
void DataTransform::CalcPosition(double const &X, double const &Y, double const &Angle){
    Position[0] = Encoder[0] + X;
    Position[1] = Encoder[1] + Y;
}
*/
