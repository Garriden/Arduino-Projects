#include <LiquidCrystal.h>
#include <TimerOne.h>

LiquidCrystal lcd(7,6,5,4,3,2);

int sensorPin = A0;
int sensorValue = 0;
int maxSegon = 0;
int maxRecord = 0;

void setup() {
  // Interrupts tiempo
  Timer1.initialize(10000);              //10ms
  Timer1.attachInterrupt(getDades);
  // Init LCD
  lcd.begin(16,2); 
  //lcd.print("Hello there");
  //lcd.setCursor(0, 1);
  //lcd.print("general rabioli");

  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void calcularMaxSegon() { 
  if(sensorValue > maxSegon) maxSegon = sensorValue;
}

void calcularMaxRecord() { 
  if(maxSegon > maxRecord) maxRecord = maxSegon;
}

void getDades() {
  sensorValue = analogRead(sensorPin);
  calcularMaxSegon();
}

void printPantalla() {
  lcd.setCursor(0, 0);
  lcd.print(maxSegon);
  lcd.setCursor(10, 0);
  lcd.print(maxRecord);
}

void loop() {
  calcularMaxRecord();
  printPantalla();
  maxSegon = 0;
  delay(1000); 
}
