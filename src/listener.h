#ifndef LISTENER_H
#define LISTENER_H

#include <stdint.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "globals.h"

uint16_t clasificarRead(uint16_t value) {
  if(value < 150)
    return NOINPUT;
  else
    if(value >= 150 && value < 350)
      return UNO;
    else
      if(value >= 350 && value < 500)
        return DOS;
      else
        if(value >= 500 && value < 725)
          return TRES;
        else
          if(value >= 725 && value < 825)
            return CUATRO;
          else
            return CINCO;
}

bool read() {
  uint8_t boton = clasificarRead(analogRead(0));

  if(boton == NOINPUT || activado) return activado = false;

  activado = true;
  switch(boton){
    case UNO:
      power = !power;
      return true;
    case DOS:
      uint32_t color;
      (stripFront.getPixelColor(0)) ? color = colorArray[colorFront] : color = 0;
      for (uint16_t i=0; i < stripFront.numPixels(); i++) {
        stripFront.setPixelColor(i, color);
      }
      stripFront.show();
      return false;
    case TRES:
      change = !change;
      return true;
    case CUATRO:
      (colorFront <= 7) ? colorFront = colorFront+1 : colorFront = 0;
      for (uint16_t i=0; i < stripFront.numPixels(); i++) {
        stripFront.setPixelColor(i, colorArray[colorFront]);
      }
      stripFront.show();
      return false;
    case CINCO:
      (numEfecto < lengthEfectos-1) ? numEfecto++ : numEfecto = 0;
      return true;
  }
}

bool readAndDelay(){
  for(uint16_t i=0; i <= wait; i++) {
    delay(1);
    if(read()) return true;
  }
  return false;
}

#endif
