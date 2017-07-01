#include <Adafruit_NeoPixel.h>
#include <stdint.h>
#include <Arduino.h>

#include "efectos.h"

uint32_t Tiempo;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(300-105, 6, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel stripFront = Adafruit_NeoPixel(20, 4, NEO_GRB + NEO_KHZ800);

void (*efectos[10])(Adafruit_NeoPixel&) = {
  apagar,
  allOnWheel,
  colorWipe,
  randomLeds,
  colorWipeComb,
  colorWipeComb4,
  theaterChase,
  rainbow,
  rainbowCycle,
  theaterChaseRainbow
};
const uint8_t lengthEfectos = 10;
uint8_t numEfecto = 0;

void setup() {
  //Serial.begin(9600);
  strip.begin();
  strip.show();
  //stripFront.begin();
  //stripFront.show();
}

void loop() {
  if(power){
    for(Tiempo = 0;  Tiempo < 1;){
      (*efectos[numEfecto])(strip);
        Tiempo++;
    }
    (numEfecto < lengthEfectos-1) ? numEfecto++ : numEfecto = 0;
  }else{
    apagar(strip);
  }

}
