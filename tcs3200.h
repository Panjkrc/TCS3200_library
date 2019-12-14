#ifndef tcs3200_h
#define tcs3200_h
 
#include <Arduino.h>

class tcs
{
public:
    tcs3200(uint8_t S0, uint8_t S1, uint8_t S2, uint8_t S3, uint8_t output);
    int colorRead(char color = 'c', int scaling = 20);
 
private:
    uint8_t _S0;
    uint8_t _S1;
    uint8_t _S2;
    uint8_t _S3;
    uint8_t _output;
};
 
#endif