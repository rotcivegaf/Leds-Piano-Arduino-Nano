#include <Adafruit_NeoPixel.h>
#include <stdint.h>
#include <Arduino.h>

#include "efectos.h"

uint32_t i;

void (*efectos[9])(Adafruit_NeoPixel&) = {
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

void setup() {
  strip.begin();
  strip.show();
  stripFront.begin();
  stripFront.show();
}

void loop() {
  if(power){
    for(i = 0;  i < ciclo;){
      (*efectos[numEfecto])(strip);
      if(change) i++;
    }
    (numEfecto < lengthEfectos-1) ? numEfecto++ : numEfecto = 0;
  }else{
    apagar(strip);
  }
}
