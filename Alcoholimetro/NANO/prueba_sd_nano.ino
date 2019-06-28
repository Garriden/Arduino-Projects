#include <SD.h>

int CS_PIN = 4; 
File file; 

void setup() {
  Serial.begin(9600); // start serial connection to print out debug messages and data
  
  pinMode(CS_PIN, OUTPUT); 
  
  if (!SD.begin(CS_PIN)) { // Initialize SD card
    Serial.println("Could not initialize SD card.");
  }
  
  if (SD.exists("file.txt")) { // if "file.txt" exists, fill will be deleted
    Serial.println("File exists.");
  }
}


void writeFile() {
  file = SD.open("file.txt", FILE_WRITE); // open "file.txt" to write data
  if (file) {
    int number = random(10); // generate random number between 0 and 9
    file.println(number); // write number to file
    file.close(); // close file
    Serial.print("Wrote number: "); // debug output: show written number in serial monitor
    Serial.println(number);
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

void loop() {
  writeFile();
  readFile();
 
  delay(5000); // wait for 5000ms
}
