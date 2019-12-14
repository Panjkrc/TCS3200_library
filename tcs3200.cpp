#include "Arduino.h"
#include "NTC_temp.h"


tcs3200::tcs3200(uint8_t S0, uint8_t S1, uint8_t S2, uint8_t S3, uint8_t output){
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(sensorOut, INPUT);


}
 
int tcs3200::colorRead(char color = 'c', int scaling = 20){
    switch (scaling){
    case 0:
      digitalWrite(S0,LOW);
      digitalWrite(S1,LOW);
    break;
    
    case 2:
      digitalWrite(S0,LOW);
      digitalWrite(S1,HIGH);
    break;
    
    case 20:
      digitalWrite(S0,HIGH);
      digitalWrite(S1,LOW);
    break;
    
    case 100:
      digitalWrite(S0,HIGH);
      digitalWrite(S1,HIGH);
    break;
    
    default:
      digitalWrite(S0,LOW);
      digitalWrite(S1,LOW);
    break;
      
  }

  
  switch (color){
    case 'r':
      digitalWrite(S2,LOW);
      digitalWrite(S3,LOW);
    break;
    
    case 'b':
      digitalWrite(S2,LOW);
      digitalWrite(S3,HIGH);
    break;
    
    case 'c':
      digitalWrite(S2,HIGH);
      digitalWrite(S3,LOW);
    break;
    
    case 'g':
      digitalWrite(S2,HIGH);
      digitalWrite(S3,HIGH);
    break;
    
    default:
      digitalWrite(S2,HIGH);
      digitalWrite(S3,LOW);
    break;
    
  }

  return pulseIn(sensorOut, LOW);
}
