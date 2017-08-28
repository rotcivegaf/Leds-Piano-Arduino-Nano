#include <Adafruit_NeoPixel.h>
#include <stdint.h>
#include <Arduino.h>

#include "efectos.h"

const uint8_t lengthEfectos = 9;

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
  //Serial.begin(9600);
  strip.begin();
  strip.show();
  stripControl.begin();
  stripControl.show();
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
