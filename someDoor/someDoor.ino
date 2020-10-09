#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"

#define SENSOR  8
#define SD_ChipSelectPin 10

TMRpcm tmrpcm;

int doorOpened = 0;
int doorOpenedCount = 0;
bool alreadyPlaying = false;

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR, INPUT_PULLUP);

  tmrpcm.speakerPin = 9;

  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }
/*
  Serial.println("Playing");

  tmrpcm.setVolume(5);
  tmrpcm.quality(1);
  tmrpcm.play("Escurso.wav");
*/
}

void loop() {
  
  // read the state of the pushbutton value:
  doorOpened = digitalRead(SENSOR);

  if(doorOpened) {
    doorOpenedCount++;
  } else {
    doorOpenedCount = 0;
    tmrpcm.disable();

    alreadyPlaying = false;
  }

  if(doorOpenedCount > 10 and !alreadyPlaying) {
    playMusic();
  } else {
    //stopMusic();
  }

  Serial.println(doorOpened);
  delay(1);
}

void playMusic() {
  tmrpcm.setVolume(5);
  tmrpcm.quality(1);
  //tmrpcm.play("Escurso.wav");
  tmrpcm.play("SOMEBODY.wav");

  alreadyPlaying = true;
}
