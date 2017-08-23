#ifndef LISTENER_H
#define LISTENER_H

#include <stdint.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "globals.h"

bool read() {
  uint16_t analogValue = analogRead(0);
  activado = false;
  if(analogValue < 150) return activado;

  if(!activado){
    if (analogValue >= 150 && analogValue < 350){ //on off inside strip
      power = !power;
      activado = true;
    }
    if (analogValue >= 350 && analogValue < 500){ // on of front strip
      uint32_t color;
      (stripFront.getPixelColor(0)) ? color = colorArray[colorFront] : color = 0;
      for (uint16_t i=0; i < stripFront.numPixels(); i++) {
        stripFront.setPixelColor(i, color);
      }
      stripFront.show();
    }
    if (analogValue >= 500 && analogValue < 725){ // change inside effects
      change = !change;
      activado = true;
    }
    if (analogValue >= 725 && analogValue < 825){ // change front color
      (colorFront <= 7) ? colorFront = colorFront+1 : colorFront = 0;
      for (uint16_t i=0; i < stripFront.numPixels(); i++) {
        stripFront.setPixelColor(i, colorArray[colorFront]);
      }
      stripFront.show();
    }
    if (analogValue >= 825){ // change efect
      (numEfecto < lengthEfectos-1) ? numEfecto++ : numEfecto = 0;
    }
  }
  return activado;
}

bool readAndDelay(){
  for(uint16_t i=0; i <= wait; i++) {
    delay(1);
    if(read()) return true;
  }
  return false;
}

#endif
