#ifndef DATAFROMSTM_H
#define DATAFROMSTM_H

#include <QByteArray>

typedef union{
    uint8_t Uint8[4];
    float F;
} Uint8ToFloat;

typedef union{
    uint8_t Uint8[2];
    int16_t I;
} Uint8ToInt;

typedef union{
    uint8_t Uint8[2];
    uint16_t Uint;
} Uint8ToUint;

#endif // DATAFROMSTM_H
