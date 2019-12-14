/* Example program for using TCS3200 color sensor
 * author: Panjkrc
 * date: 12/14/2019
 * url: https://github.com/Panjkrc/tcs3200/
 */


#include <tcs3200.h>

int red, green, blue, clear;

tcs3200 tcs(2, 3, 4, 5, 6); // (S0, S1, S2, S3, output pin)  //

void setup() {
  Serial.begin(9600);
}

void loop() {
  //red = tcs.colorRead('r', 0);    //scaling can also be put to 0%, 20%, and 100% (default scaling is 20%)   ||    read more at: https://www.mouser.com/catalog/specsheets/TCS3200-E11.pdf
  //red = tcs.colorRead('r', 20);
  //red = tcs.colorRead('r', 100);

  red = tcs.colorRead('r');   //reads color value for red
  Serial.print("R= ");
  Serial.print(red);
  Serial.print("    ");
  
  green = tcs.colorRead('g');   //reads color value for green
  Serial.print("G= ");
  Serial.print(green);
  Serial.print("    ");

  blue = tcs.colorRead('b');    //reads color value for blue
  Serial.print("B= ");
  Serial.print(blue);
  Serial.print("    ");

  clear = tcs.colorRead('c');    //reads color value for white(clear)
  Serial.print("W(clear)= ");
  Serial.print(clear);
  Serial.print("    ");

  Serial.println();

  delay(200);

}