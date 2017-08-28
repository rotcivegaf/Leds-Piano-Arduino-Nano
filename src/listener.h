#ifndef LISTENER_H
#define LISTENER_H

#include <stdint.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

enum clasificaciones {NOINPUT=0, UNO=1, DOS=2, TRES=3, CUATRO=4, CINCO=5};

bool activado = false;
uint16_t wait = 1;
bool power = false;
bool change = true;
uint8_t ciclo = 3;
uint32_t numEfecto = 0;
bool stripIsSelected = true;
//Adafruit_NeoPixel stripFront = Adafruit_NeoPixel(, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(300-105, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripControl = Adafruit_NeoPixel(6, 7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripSelected = strip;

uint16_t clasificarRead(uint16_t value) {
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
          if(value >= 725 && value < 825)
            return CINCO;
          else
            return NOINPUT;
}

bool changeSelectStrip(){
  stripIsSelected ?  stripSelected = stripControl : stripSelected = stripControl;
  stripIsSelected = !stripIsSelected;
  
  stripControl.setPixelColor(3, strip.getPixelColor(0));
  stripControl.setBrightness(50);
  stripControl.show();
  return false;
}

bool read() {
  uint8_t boton = clasificarRead(analogRead(0));
  if(boton == NOINPUT) return activado = false;
  activado = true;
  switch(boton){
    case UNO:// ON/OFF
      power = !power;
      return true;
    case DOS:// select strip
      return changeSelectStrip();
    case TRES://cambio efectos
      change = !change;
      return true;
    case CUATRO://cambiar un efecto
      stripControl.setPixelColor(3, stripControl.Color(50,0,100));
      numEfecto++;
      return true;
    case CINCO:
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

void cambiarWait(uint16_t &wait){
  /*if(wait != 1){
    wait == 1;
  }*/
}

#endif
