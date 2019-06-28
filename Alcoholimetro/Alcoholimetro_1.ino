#include <LiquidCrystal.h>
#include <TimerOne.h>
#include <SD.h>
#include <SimpleTimer.h>

SimpleTimer timer;

File file; 

LiquidCrystal lcd(10,7,6,5,3,2);

int buttonEnter_PIN = 8;
int buttonMenu_PIN = 9;
int CS_PIN = 4; 
int sensorPin = A0;
int sensorValue = 0;
int maxSegon = 0;
int maxRecord = 0;
int buttonEnterState = 0;
int buttonMenuState = 0;
bool modoMenu = true;
bool estartMenu = true;
bool startStart = false; 
bool cambiaEstado = false;
bool nameMode = false;
bool pampallugues = false;
bool puedoMostrarRes = false;
int P = 0,   pPos = 0;
int posMenu = 1;
int tim = 9;
int c = -1;
char C = ' ';
char Rec[8];
char Leido[100];
int LeidoI = 0;
int RecI = 0;
int timerID;
bool ojo = false;
bool ojo2 = false;
bool acabar = false;
int contadorCaracters = 0;
bool mostrarElsRecords = false;

void setup() {
  // Interrupts tiempo
  Timer1.initialize(10000);              //10ms
  Timer1.attachInterrupt(getDades);
  // Init LCD
  lcd.begin(16,2); 

  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(CS_PIN, OUTPUT);
  pinMode(buttonEnter_PIN, INPUT);
  pinMode(buttonMenu_PIN, INPUT);

  timerID = timer.setInterval(1000, repeatMe);
  
  //Inicializar SD
  if (!SD.begin(CS_PIN)) { // Initialize SD card
    Serial.println("Could not initialize SD card.");
  }
  if (SD.exists("file.txt")) { // if "file.txt" exists, fill will be deleted
    Serial.println("File exists.");
  }
  delay(50);
  lcd.setCursor(0, 0);
  lcd.print("*");
  
}

// Timer
void repeatMe() {
  tim--;
  estartMenu = true;
  /*if(pampallugues) {
    if(P == 0) {
      P = 1;
      lcd.setCursor(pPos, 1);
      lcd.print("_");
    }else {*/
    if(pampallugues) {
      lcd.setCursor(pPos, 1);
      if(c == -1) C = '_';
      else C = 'A'+c;
      lcd.print(C);

    }
  //}
}

// SD  /////////////////////////////////////////

void writeFile() { 

char CopiarAntes[48] = {""};
char CopiarDespues[48] = {""};

    int borrarCaracter = 0;
  file = SD.open("file.txt", FILE_READ); // open "file.txt" to read data
  if (file) {
   
    // mirar donde escribir
    char character;  
    while (((character = file.read()) != -1) && (!acabar)) { // this while loop reads data stored in "file.txt" and prints it to serial monitor
      borrarCaracter++;
      if(character == '\n') {
        LeidoI = 0;
        ojo = false;
        int test = atoi(Leido);
        Serial.println(test);
        if(test > maxRecord) acabar = true;
        if(!acabar) borrarCaracter = 0;
      }else if(ojo) {

          Leido[LeidoI] = character;
          LeidoI++;
        
      } else if(character == ':') ojo = true;
      contadorCaracters++;
    }
      acabar = false;   
      //clearPantalla();
      delay(20);
     
      LeidoI = 0;
      file.close();

  }
 

  file = SD.open("file.txt", FILE_READ); // open "file.txt" to read data
  int II = 0;
  int III = 0;
  if (file) {
    char character;
    while(II < (contadorCaracters-borrarCaracter)) { 
      character = file.read(); 
      CopiarAntes[II] = character; 
      II++;
    }
    
    while ((character = file.read()) != -1) { 
      CopiarDespues[III] = character;
      III++;
      //Serial.print(character);
    }

  II = 0;
  III = 0;
      
  Serial.print(CopiarAntes);

  Serial.println("-----------------------");

  Serial.print(CopiarDespues);

 // Serial.println("-----------------------");

  //Serial.print(CopiarDespues);
  file.close();
  }

 contadorCaracters = 0;

 SD.remove("file.txt");

 file = SD.open("file.txt", FILE_WRITE); // open "file.txt" to write data
 
  if (file) {
     file.print(CopiarAntes);
   
    // escribir
    file.print(Rec);
    //file.print(Rec[0]);
    file.print(": ");               // write number to file
    file.println(maxRecord);        // write number to file

     file.println(CopiarDespues);
    
    file.close();                   // close file
  } else {
    Serial.println("Could not open file (writing).");
  }
}

void readFile() {
  file = SD.open("file.txt", FILE_READ); // open "file.txt" to read data
  if (file) {
    Serial.println("--- Reading start ---");
    char character;
    lcd.setCursor(0, 0);
    while ((character = file.read()) != -1) { // this while loop reads data stored in "file.txt" and prints it to serial monitor
      Serial.print(character);
      if(character == '\n') lcd.setCursor(0,1);
      lcd.print(character);
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
  lcd.setCursor(0, 0);
  lcd.print("act:");
  lcd.setCursor(5, 0);
  lcd.print(maxSegon);
  if(maxSegon < 99) {
    lcd.setCursor(7, 0);
    lcd.print(" ");
  }
  lcd.setCursor(15, 0);
  lcd.print(tim);
  lcd.setCursor(0, 1);
  lcd.print("max:");
  lcd.setCursor(5, 1);
  lcd.print(maxRecord);
  //Serial.println(maxSegon);

  if(tim < 0)   clearPantalla();
}

void clearPantalla() {
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

void cuentaAtras() {
  lcd.setCursor(15, 0);
  lcd.print(3);
  delay(1000);
  lcd.setCursor(15, 0);
  lcd.print(2);
  delay(1000);
  lcd.setCursor(15, 0);
  lcd.print(1);

  timer.restartTimer(timerID);
  
  delay(1000);
}

void mostrarResultados() {
  lcd.setCursor(0, 0);
  lcd.print("result:");
  lcd.setCursor(8, 0);
  lcd.print(maxRecord);
}

void quickReset() {
  nameMode = false;
  puedoMostrarRes = false;
  modoMenu = true;
  clearPantalla();
  pPos = 0;
  maxRecord = 0;
  maxSegon = 1;
  RecI = 0;
  //for (int i = 0; i < 8; i++) Rec[i] = ' ';
  tim = 9;
}

void salvarNombre() {
  clearPantalla();
  lcd.setCursor(2, 0);
  lcd.print("saving");
  delay(1000);
  lcd.setCursor(9, 0);
  lcd.print(".");
  delay(1000);
  writeFile();
  lcd.setCursor(10, 0);
  lcd.print(".");
  delay(500);
  lcd.setCursor(11, 0);
  lcd.print(".");
  delay(1000);
  lcd.setCursor(2, 1);
  lcd.print("saved");
  delay(1000);
  
  quickReset();
  
  lcd.setCursor(0, 0);
  lcd.print("*");
}

void cojerNombre() {
  lcd.setCursor(2, 1);
  lcd.print("name:");
  pampallugues = true;

  buttonEnterState = digitalRead(buttonEnter_PIN);
  buttonMenuState = digitalRead(buttonMenu_PIN);
  timer.run();
  if((buttonMenuState == HIGH) && (estartMenu)) {
    c++;
    estartMenu = false;
  } else if((buttonEnterState == HIGH)&& (estartMenu)) {

 
    
    if(c == -1) {
      pampallugues = false;
      salvarNombre();
    } else {
      Rec[RecI] = C;
      RecI++;
      pPos++;
      estartMenu = false;
      c = -1;
    }
  }
  
  
}

void muestraMenu() {
  buttonEnterState = digitalRead(buttonEnter_PIN);
  buttonMenuState = digitalRead(buttonMenu_PIN);
  lcd.setCursor(2, 0);
  lcd.print("Start");
  lcd.setCursor(2, 1);
  lcd.print("Records");
  if(cambiaEstado) { 
    cambiaEstado = false;
    if(posMenu == 0) {
      lcd.setCursor(0, 0);
      lcd.print("*");
      lcd.setCursor(0, 1); 
      lcd.print(" ");
      posMenu = 1;
    }
    else {
      lcd.setCursor(0, 0); 
      lcd.print(" ");
      lcd.setCursor(0, 1); 
      lcd.print("*");
      posMenu = 0;
    }
    
  }
      
  if(buttonMenuState == HIGH) {
    timer.run();
    if(estartMenu) cambiaEstado = true;
    estartMenu = false;
  }

  else if(buttonEnterState == HIGH) {
    if(posMenu == 1) {   // start
      modoMenu = false;
      clearPantalla();
      cuentaAtras();
      tim = 10;
      puedoMostrarRes = true;
      maxSegon = 1;
      maxRecord = 0;
    }
    else if (posMenu == 0) {  // records

      modoMenu = false;
      clearPantalla();
      mostrarElsRecords = true;
    }
    
  
  }
 
}

void loop() {
  if(nameMode) {

    cojerNombre();
  }
  else if((tim < 0) && puedoMostrarRes) {
    mostrarResultados();
    if(buttonEnterState == HIGH) {
      nameMode = true;
      puedoMostrarRes = false;
      pPos = 8;
    }
    
  } else if(mostrarElsRecords) {
         readFile();
    
  } else {
    if(modoMenu) {
      muestraMenu();
      maxRecord = 0;
      maxSegon = 1;
      tim = 10;
    } else {
      timer.run();
      calcularMaxRecord();
      printPantalla();
      maxSegon = 0;
    }
  }
  delay(10); 
}

