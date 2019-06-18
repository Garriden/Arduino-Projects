#include <Servo.h>

Servo myservo;

int trig = 6;
int echo = 4;

int pos = 0;
int distancia = 0;
int tiempo;
int distanciaAnterior = 0;
int D;

void setup() {
  myservo.attach(9);
  //Serial.begin (9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  myservo.write(0);
  delay(1000);
}

void moverServo() {
  //Serial.println("moviendo servo");
  for(pos = 0; pos <= 50; ++pos) {
    myservo.write(pos);
    delay(15);
  }
    delay(2000);
  for(pos = 50; pos >= 0; --pos) {
    myservo.write(pos);
    delay(15);
  }
  

  
  
}

void loop() {
  
  
  
  digitalWrite(trig,LOW);
  delayMicroseconds(5);
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  
  tiempo=pulseIn(echo, HIGH);
  
  distancia= int(0.017*tiempo);

  D = (distancia + distanciaAnterior) / 2;  
/*
  Serial.print("Distancia D: ");
  Serial.print(D);
  Serial.println(" cm");
*/
  if (D < 100 && D > 40)
  {
    moverServo();
    //delay(10000);
  }

  distanciaAnterior = distancia;
  
  delay(50);
  
}
