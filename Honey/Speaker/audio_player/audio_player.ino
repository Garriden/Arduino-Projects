#include <SD.h>                       // need to include the SD library
#include <TMRpcm.h>                   // also need to include this library...
#include <SPI.h>

#define SD_ChipSelectPin 10 

TMRpcm tmrpcm;

void playMusic() 
{
  tmrpcm.setVolume(5);
  tmrpcm.quality(1);
  //tmrpcm.play("kanto.wav");
  //tmrpcm.play("bebellorando.wav");
  tmrpcm.play("bebe_8b.wav");
  //tmrpcm.play("Escurso.wav");
  //tmrpcm.play("SOMEBODY.wav");
}

void setup()
{
  tmrpcm.speakerPin = 9;

  Serial.begin(9600);

  if(!SD.begin(SD_ChipSelectPin))
  {
    Serial.println("SD fail");
    return;
  } else {
    Serial.println("SD OK");
  }

  playMusic();
}


void loop() {
  //playMusic();
}
