/*
  SD card read/write

***********************************************************************************
OJOOOOOOO importante, en arduino DUE: SCK, MOSI y MISO están escondidos.

mirate esto: http://www.robgray.com/temp/Due-pinout-WEB.png

Con unas de los conjuntos de 6 patitas que sobresalen en el centro de la placa.
Concretamente las de la derecha, dedicadas a comunicación SPI.

Con Arduino DUE solo te funcionará este codigo si enchufas los cables alli.

El pin CS solo puede ser el 4, 10 o 52.
************************************************************************************

  CS - pin 4 
  
 */

#include <SPI.h>
#include <SD.h>

File myFile;

// Pins accelerometer
const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis (only on 3-axis models)

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for serial port to connect. Needed for native USB port only

  Serial.print("Initializing SD card...");
  pinMode(4, OUTPUT);   // CS

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

}

void loop() {
  // print the sensor values:
  Serial.print(analogRead(xpin));
  // print a tab between values:
  Serial.print("\t");
  Serial.print(analogRead(ypin));
  // print a tab between values:
  Serial.print("\t");
  Serial.print(analogRead(zpin));
  Serial.println();
  // delay before next reading:
  delay(100);

  
  //ESCRIBIR a SD
   myFile = SD.open("test.txt", FILE_WRITE);
   
  if (myFile) {
    //Serial.print("escric en: test.txt...");

    //Serial.print(analogRead(xpin));
    myFile.print(analogRead(xpin));   //Eje X
    myFile.print("\t");   //tab
    //Serial.print("\t"); //tab

    //Serial.print(analogRead(ypin));
    myFile.print(analogRead(ypin));   //Eje Y
    myFile.print("\t");   //tab
    //Serial.print("\t"); //tab

   // Serial.print(analogRead(zpin));
    myFile.print(analogRead(zpin));   //Eje Z
    myFile.print("\t");   //tab
    //Serial.print("\t"); //tab
    //Serial.println();
    myFile.println();   //tab
    // close the file:
    myFile.close();
    //Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
   }
 delay(500);
   
}
