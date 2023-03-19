// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'
// This demo code returns raw readings, public domain

#include <stdint.h>
#include "TouchScreen.h"
#include "Adafruit_GFX.h"    // Core graphics library
#include "MCUFRIEND_kbv.h"   // Hardware-specific library

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
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
/*
     for(int ii = 0; ii < 150; ++ii) {
       for(int jj = 0; jj < 240; ++jj) {
        tft.drawPixel(ii, jj, TFT_RED);
      }
     }
          for(int ii = 320; ii > 170; --ii) {
       for(int jj = 240; jj > 0; --jj) {
        tft.drawPixel(ii, jj, TFT_GREEN);
      }
     }
  */
}

/* 16x12 */
void Draw20x20Chunk(int x, int y, int color)
{
  for(int ii = (x*20); ii < ((x+1)*20); ++ii) {
    for(int jj = (y*20); jj < ((y+1)*20); ++jj) {
      tft.drawPixel(ii, jj, color);
    }
  }
} 

int perraka = 25;
int color = TFT_BLACK;
int par = 0;
int impar = 0;
int iterations = 0;
//320 x 240
void loop(void) {

  //delay(1000);

  for(int ii = 0; ii < 16; ++ii) {
    for(int jj = 0; jj < 12; ++jj) {
      int randomNumber = random(2);
      //Serial.println(randomNumber);

      if(randomNumber == 0) {
        color = TFT_GREEN;
        par++;
      } else {
        color = TFT_RED;
        impar++;        
      }
      Draw20x20Chunk(ii, jj, color);
      //delay(100);

      if(++iterations == 100) {
        Serial.print(par);
        Serial.print(",");
        Serial.println(impar);
        par = 0;
        impar = 0;
        iterations = 0;
      }

    }
  }

}