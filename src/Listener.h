#ifndef LISTENER_H
#define LISTENER_H

#include <stdint.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

using namespace std;

enum botones {NOINPUT=0, POWERSTRIP=1, CHANGESTRIP=2, SVCHANGEMODE=3, SVCHANGEDELAY=4, SVNOSE=5};

class Listener {
  private:
    bool activado = false;

    uint8_t read();

  public:
    bool listen();
};

bool Listener::listen(){

  return false;
}

uint8_t Listener::read() {
  uint16_t analogValue = analogRead(0);
  uint8_t ret = NOINPUT;

  if(analogValue < 150){
    activado = false;
    return ret;
  }

  if (!activado){
    activado = true;
    if (analogValue >= 150 && analogValue < 350)
      ret = POWERSTRIP;
    if (analogValue >= 350 && analogValue < 500)
      ret = CHANGESTRIP;
    if (analogValue >= 500 && analogValue < 725)

      ret = SVCHANGEMODE;
    if (analogValue >= 725 && analogValue < 825)
      ret = SVCHANGEDELAY;
    if (analogValue >= 825)
      ret = SVNOSE;
  }

  return ret;
}

/*
uint16_t Wait = 1;
uint32_t Tiempo;
bool ChangeMode = true;
bool Old8 = false;
bool Old7 = false;
bool Cambio = false;
*/

/*
bool readChange(){
  if(digitalRead(8)){
    if(!Old8){
      Old8 = true;
      ChangeMode = !ChangeMode;
    }
  }else{
    Old8 = false;
  }

  bool ret = false;
  if(digitalRead(7)){
    if(!Old7){
      Old7 = true;
      ret = true;
    }
  }else{
    Old7 = false;
  }
  return Cambio = ret;
}

void readDelay(){
  if(digitalRead(12) == HIGH){
    Wait += 1;
    return;
  }
  if(digitalRead(10) == HIGH){
    if(Wait <= 0){
      Wait = 1;
    }else{
      Wait -= 1;
    }
  }
}

bool listen(){
  readDelay();
  return readChange();
}

bool waitListen(){
  bool ret;
  for(uint16_t i=0; i <= Wait; i++) {
    ret = readChange();
    delay(1);
    readDelay();
    if(ret) return ret;
  }
  return ret;
}
*/
#endif