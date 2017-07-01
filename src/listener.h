#ifndef LISTENER_H
#define LISTENER_H

#include <stdint.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

enum botones {NOINPUT=0, POWERSTRIP=1, CHANGESTRIP=2, SVCHANGEMODE=3, SVCHANGEDELAY=4, SVNOSE=5};

bool activado = false;
uint16_t wait = 1;
bool power = true;

bool read() {
  uint16_t analogValue = analogRead(0);
  if(analogValue < 150){
    activado = false;
    return false;
  }
  if(!activado){
    activado = true;
    if (analogValue >= 150 && analogValue < 350){
      power = !power;
      return true;
    }else{
      return true;
      //if (analogValue >= 350 && analogValue < 500){

      //}
    }
  }
  return false;


/*  if (analogValue >= 150 && analogValue < 350)
    ret = POWERSTRIP;
  if (analogValue >= 350 && analogValue < 500)
    ret = CHANGESTRIP;
  if (analogValue >= 500 && analogValue < 725)

    ret = SVCHANGEMODE;
  if (analogValue >= 725 && analogValue < 825)
    cambiarWait(wait);
  if (analogValue >= 825)
    ret = SVNOSE;
*/
}

bool readAndDelay(){
  for(uint16_t i=0; i <= wait; i++) {
    delay(1);
    if(read()) return true;
  }
  return false;
}

void cambiarWait(uint16_t &wait){
  /*if(wait != 1){
    wait == 1;
  }*/
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
