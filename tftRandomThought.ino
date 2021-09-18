// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'
// This demo code returns raw readings, public domain

#include <stdint.h>
#include "TouchScreen.h"
#include "Adafruit_GFX.h"    // Core graphics library
#include "MCUFRIEND_kbv.h"   // Hardware-specific library

#define WHITE    0x0000
#define CYAN     0xF800
#define PURPLE   0x07E0
#define BLACK    0xFFFF
#define RED      0x8410

MCUFRIEND_kbv tft;

long randomNumber;
int buff = 0;
float ones = 0;
float zeros = 0;
float onesPercentage = 0;
float zerosPercentage = 0;

void setup(void) {
  Serial.begin(9600);

  randomSeed(analogRead(A0));

  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.invertDisplay(true);
  tft.setRotation(1);
  tft.fillScreen(BLACK);

     for(int ii = 0; ii < 150; ++ii) {
       for(int jj = 0; jj < 240; ++jj) {
        tft.drawPixel(ii, jj, CYAN);
      }
     }


          for(int ii = 320; ii > 170; --ii) {
       for(int jj = 240; jj > 0; --jj) {
        tft.drawPixel(ii, jj, PURPLE);
      }
     }
  
}

//320 x 240
void loop(void) {

  if(ones > 20) {
    
     for(int ii = 0; ii < 325; ++ii) {
       for(int jj = 0; jj < 240; ++jj) {
        tft.drawPixel(ii, jj, CYAN);
      }
     }
 }


 
  randomNumber = random(1,1000);
  randomNumber = randomNumber%2;

  if(randomNumber) {
    ones++;
  } else {
    zeros++;
  }

  onesPercentage = ones/(ones+zeros);
  zerosPercentage = zeros/(ones+zeros);

  //Serial.println(analogRead(A0));
  //Serial.println(randomNumber); 
  //Serial.print(onesPercentage); 
  //Serial.print("  /  ");
  //Serial.println(zerosPercentage);
    
  delay(100);
}
