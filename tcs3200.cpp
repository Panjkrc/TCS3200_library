/*  CPP FILE - TCS3200 library
 *  TCS3200 color sensor library
 *  author: Panjkrc
 *  date: 12/14/2019
 *  url: https://github.com/Panjkrc/TCS3200_library
 */

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
 
int tcs3200::colorRead(char color, int scaling){
    
    switch (scaling){
    case 0:
      digitalWrite(_S0,LOW);        // Set scaling to 0%(scaling is turned OFF)
      digitalWrite(_S1,LOW);
    break;
    
    case 2:
      digitalWrite(_S0,LOW);        // Set scaling to 2%
      digitalWrite(_S1,HIGH);
    break;
    
    case 20:                        // Set scaling to 20%
      digitalWrite(_S0,HIGH);
      digitalWrite(_S1,LOW);
    break;
    
    case 100:                       // Set scaling to 100%
      digitalWrite(_S0,HIGH);
      digitalWrite(_S1,HIGH);
    break;
    
    default:                        // Set scaling to 20%(default scaling is 20%)
      digitalWrite(_S0,LOW);
      digitalWrite(_S1,LOW);
    break;
      
  }

  
  switch (color){
    case 'r':                         // Setting red filtered photodiodes to be read
      digitalWrite(_S2,LOW);
      digitalWrite(_S3,LOW);
    break;
    
    case 'b':                         // Setting blue filtered photodiodes to be read
      digitalWrite(_S2,LOW);
      digitalWrite(_S3,HIGH);
    break;
    
    case 'c':                         // Setting clear photodiodes(no filters on diodes) to be read
      digitalWrite(_S2,HIGH);
      digitalWrite(_S3,LOW);
    break;
    
    case 'g':                         // Setting green filtered photodiodes to be read
      digitalWrite(_S2,HIGH);
      digitalWrite(_S3,HIGH);
    break;
    
    default:
      digitalWrite(_S2,HIGH);
      digitalWrite(_S3,LOW);
    break;
    
  }

  return pulseIn(_output, LOW);     // Reads and returns the frequency of selected color
}

int tcs3200::colorMax(){

    int r, g, b;
    
    r = colorRead('r');
    g = colorRead('g');
    b = colorRead('b');

    if( (r>g) && (r>b) )
        return 0;

    if( (g>r) && (g>b) )
        return 1;

    if( (b>r) && (b>g) )
        return 2;

    if( r==g && r==b)
        return 3;

    else return 4;
}

int tcs3200::colorMin(){

    int r, g, b;
    
    r = colorRead('r');
    g = colorRead('g');
    b = colorRead('b');

    if( (r<g) && (r<b) )
        return 0;

    if( (g<r) && (g<b) )
        return 1;

    if( (b<r) && (b<g) )
        return 2;

    if( r==g && r==b)
        return 3;

    else return 4;
}
