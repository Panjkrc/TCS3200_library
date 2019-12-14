#include "Arduino.h"
#include "tcs3200.h"


tcs3200::tcs3200(uint8_t S0, uint8_t S1, uint8_t S2, uint8_t S3, uint8_t output){
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(output, INPUT);

    _S0 = S0;
    _S1 = S1;
    _S2 = S2;
    _S3 = S3;
    _output = output;

}
 
int tcs3200::colorRead(char color = 'c', int scaling = 20){
    switch (scaling){
    case 0:
      digitalWrite(_S0,LOW);
      digitalWrite(_S1,LOW);
    break;
    
    case 2:
      digitalWrite(_S0,LOW);
      digitalWrite(_S1,HIGH);
    break;
    
    case 20:
      digitalWrite(_S0,HIGH);
      digitalWrite(_S1,LOW);
    break;
    
    case 100:
      digitalWrite(_S0,HIGH);
      digitalWrite(_S1,HIGH);
    break;
    
    default:
      digitalWrite(_S0,LOW);
      digitalWrite(_S1,LOW);
    break;
      
  }

  
  switch (color){
    case 'r':
      digitalWrite(_S2,LOW);
      digitalWrite(S3,LOW);
    break;
    
    case 'b':
      digitalWrite(_S2,LOW);
      digitalWrite(_S3,HIGH);
    break;
    
    case 'c':
      digitalWrite(_S2,HIGH);
      digitalWrite(_S3,LOW);
    break;
    
    case 'g':
      digitalWrite(_S2,HIGH);
      digitalWrite(_S3,HIGH);
    break;
    
    default:
      digitalWrite(_S2,HIGH);
      digitalWrite(_S3,LOW);
    break;
    
  }

  return pulseIn(output, LOW);
}
