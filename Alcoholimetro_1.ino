#include <LiquidCrystal.h>
#include <TimerOne.h>
#include <SD.h>

File file; 

LiquidCrystal lcd(7,6,5,4,3,2);

int CS_PIN = 10; 
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

  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(CS_PIN, OUTPUT);
  
  //Inicializar SD
  if (!SD.begin(CS_PIN)) { // Initialize SD card
    Serial.println("Could not initialize SD card.");
  }
  if (SD.exists("file.txt")) { // if "file.txt" exists, fill will be deleted
    Serial.println("File exists.");
  }
  
}

// SD  /////////////////////////////////////////

void writeFile() {
  file = SD.open("file.txt", FILE_WRITE); // open "file.txt" to write data
  if (file) {
    file.println(maxRecord); // write number to file
    file.close(); // close file
    Serial.print("Wrote number: "); // debug output: show written number in serial monitor
    Serial.println(maxRecord);
  } else {
    Serial.println("Could not open file (writing).");
  }
}

void readFile() {
  file = SD.open("file.txt", FILE_READ); // open "file.txt" to read data
  if (file) {
    Serial.println("--- Reading start ---");
    char character;
    while ((character = file.read()) != -1) { // this while loop reads data stored in "file.txt" and prints it to serial monitor
      Serial.print(character);
    }
    file.close();
    Serial.println("--- Reading end ---");
  } else {
    Serial.println("Could not open file (reading).");
  }
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
  writeFile();
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

