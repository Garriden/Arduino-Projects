int motorPin = 5;
int buttonPin = 4;

int buttonState = 0;         // variable for reading the pushbutton status

const unsigned long MIN = 60;
const unsigned long SEC = 1000;
const unsigned long eventInterval = 30 * MIN * SEC;
unsigned long previousTime = 0;
unsigned long currentTime = 0;
 
void setup() 
{ 
  pinMode(motorPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);

  
}

void moveItPlease() {
   digitalWrite(motorPin, HIGH);
   delay(50);  // Physically it moves the blue spin -> (45min? watch eventInterval var) 
   digitalWrite(motorPin, LOW);
   delay(1000);
}
 
 
void loop() 
{ 
   currentTime = millis();
   buttonState = digitalRead(buttonPin);

   if(buttonState) {
     moveItPlease();
   } else {
     if( currentTime - previousTime >= eventInterval ) {
      moveItPlease();
      previousTime = currentTime;
     }
   }
} 
