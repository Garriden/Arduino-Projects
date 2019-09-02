/* This example shows how to use continuous mode to take
range measurements with the 6 pin VL53L0X module. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. 

Original source: https://github.com/adafruit/Adafruit_VL53L0X
Modified by Ahmad Shamshiri for RoboJax.com
Date modified: May 31, 2018 at 19:25 at Ajax, Ontario, Canada
Watch the instruciton video for this code https://youtu.be/S2jaAQEv3Yo

Pin connection
VL53L0X Pin  Arduino Pin
VCC         5V
GND         GND
SDA         A4 or SDA if available
SCL         A5 or SCL if available
GPIO1       leave it unconnected
XSHUT       D12 (digital 12 or pin 12)
*/


#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

void setup()
{
  pinMode(12,INPUT_PULLUP);
  digitalWrite(12,HIGH);
  Serial.begin(9600);
  Wire.begin();

  sensor.init();
  sensor.setTimeout(500);

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
}

void loop()
{
  int distance =sensor.readRangeContinuousMillimeters();
  //int distance =sensor.startContinuous(100);
  
 //distance = distance;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("mm");
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();
  delay(100);
} 
