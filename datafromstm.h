#ifndef DATAFROMSTM_H
#define DATAFROMSTM_H

typedef struct{
    unsigned int PWM[2];
    int Encoder[2];
    int Gyro;
    float Compass;
} DataFromSTM;

#endif // DATAFROMSTM_H
