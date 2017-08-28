#include <Adafruit_NeoPixel.h>
#include <stdint.h>
#include <Arduino.h>

#include "efectos.h"

void (*efectos[lengthEfectos])(Adafruit_NeoPixel&) = {
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
    for(numEfecto = 0;  numEfecto < ciclo;){
      (*efectos[numEfecto])(strip);
      if(change) numEfecto++;
    }
    (numEfecto < lengthEfectos-1) ? numEfecto++ : numEfecto = 0;
  }else{
    apagar(strip);
  }
}
