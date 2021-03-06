// TODO:
//
// Continus beep some centimeters before. Now when you hear the continuous beep, you already touched.
// Buy and install a bigger buzzer.
// Test and find the best "sleeping" value without receiving noise. 
// Substitute Sleep() for a simulated reading thread.

#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

const int BUZZER_PIN_ = 8;
int D = 1000;
int ii;

void setup() {
  pinMode(BUZZER_PIN_, OUTPUT);

  Serial.begin(9600);
  Wire.begin();

  sensor.init();
  sensor.setTimeout(500);
  sensor.startContinuous();  
  delay(100);
}


void loop() {
  get_distance();
  beep();
}

void beep() {
  D = clamp(D, 1, 1000);
  if(D > 70) {
    delay(D-70);
  }
  Serial.println(D);
  for(ii = 0; ii < 50; ++ii) {
    digitalWrite(BUZZER_PIN_, HIGH); 
    delay(1);
    digitalWrite(BUZZER_PIN_, LOW);
    delay(1);    
  }
}

void get_distance() {
  int distance = sensor.readRangeContinuousMillimeters();
    if(distance < 50) distance = 1000;

  D = (D * 0.5) + (distance * 0.5);
}

int clamp(int value, int min_, int max_) {
  if(value > max_) {
      value = max_;
  } else if(value < min_) {
      value = min_;
  }

  return value;
}
