#ifndef EFECTOS_H
#define EFECTOS_H

#include <stdint.h>
#include <Arduino.h>
#include "listener.h"
#include <Adafruit_NeoPixel.h>

enum colores {RED = 16711680, GREEN = 65280, BLUE = 255,
  REDGREEN = 16776960, REDBLUE = 16711935, GREENBLUE = 65535, WHITE = 8355711};

//auxiliar functions
uint32_t color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

uint32_t getColor(uint8_t x){
  switch (x) {
    case 0: return RED;
    case 1: return GREEN;
    case 2: return BLUE;
    case 3: return REDBLUE;
    case 4: return REDGREEN;
    case 5: return GREENBLUE;
    default: return WHITE;
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

//Efectos
void colorWipe(Adafruit_NeoPixel strip) {
  uint16_t wait = 1;
  uint32_t c[7] = {RED, GREEN, BLUE, REDGREEN, REDBLUE, GREENBLUE, WHITE};

  for(uint8_t j = 0; j<7; j++){
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c[j]);
      strip.show();
      if(read(wait)) return;
    }
  }
}

void colorWipeComb(Adafruit_NeoPixel strip){
  uint16_t wait = 5;
  uint32_t c1 = 0, c2 = 0;

  while(c1==c2) {
    c1 = getColor(random(0,6));
    c2 = getColor(random(0,6));
  }
  for(uint16_t j=strip.numPixels()-1, i=0; i < strip.numPixels(); i++, j--) {
    strip.setPixelColor(j, c1);
    strip.setPixelColor(i, c2);
    strip.show();
    if(read(wait)) return;
  }
}

void colorWipeComb4(Adafruit_NeoPixel strip) {
  uint16_t wait = 5;
  uint32_t c1 = 0, c2 = 0, c3, c4;
  while(c1==c2) {
    c1 = REDGREEN;
    c2 = REDBLUE;
    c3 = GREENBLUE;
    c4 = GREEN;
  }
  uint16_t i = 0;
  uint16_t j = strip.numPixels()/4;
  uint16_t k = strip.numPixels()/2;
  uint16_t l = strip.numPixels()*3/4;

  for(; i < strip.numPixels(); i++, j++, k++, l++) {
    if(j >= strip.numPixels()-1){
      j = 0;
    }
    if(k >= strip.numPixels()-1){
      k = 0;
    }
    if(l >= strip.numPixels()-1){
      l = 0;
    }

    strip.setPixelColor(i, c1);
    strip.setPixelColor(j, c2);
    strip.setPixelColor(k, c3);
    strip.setPixelColor(l, c4);

    strip.show();
    if(read(wait)) return;
  }

}

/*
void allChange(){
  uint32_t auxC, c1 = 0, c2 = 0;
  uint16_t i;
  while(!read(wait)){
    c1 = getColor(random(0,3));
    c2 = getColor(random(0,3));
    while(c1==c2) {
      c1 = getColor(random(0,3));
      c2 = getColor(random(0,3));
    }
    if(c1 > c2 ){
      auxC = c1;
      c1 = c2;
      c2 = auxC;
    }

    for(; c2 >= c1; c1++) {
      for(i=0; i< strip.numPixels(); i++) {
        strip.setPixelColor(i, c1);
      }
      if(read(wait))
        return;

      strip.show();
      delay(1);
    }
  }
}*/

//Theatre-style crawling lights.
void theaterChase(Adafruit_NeoPixel strip) {
  uint16_t wait = 300;
  uint32_t c[7] = {RED, GREEN, BLUE, REDGREEN, REDBLUE, GREENBLUE, WHITE};

  while(1){
    for(uint8_t j = 0; j<7; j++){
      for(uint8_t e = 0; e<10; e++){
        for (int8_t q=0; q < 3; q++) {
          for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
            strip.setPixelColor(i+q, c[j]);    //turn every third pixel on
          }
          strip.show();
          if(read(wait)) return;

          for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
            strip.setPixelColor(i+q, 0);        //turn every third pixel off
          }
        }
      }
    }
  }
}

void randomLeds(Adafruit_NeoPixel strip) {
  uint16_t wait = 100;
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(random(0, strip.numPixels()), 0);
    strip.setPixelColor(random(0, strip.numPixels()), random(0, 16777215));
    strip.show();
    if(read(wait)) return;
  }
}

void rainbow(Adafruit_NeoPixel strip) {
  uint16_t wait = 100;
  uint16_t i, j;
  while(!read(wait)){
    for(j=0; j<256; j++) {
      for(i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, Wheel((i+j) & 255));
      }
      strip.show();
      if(read(wait)) return;
    }
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(Adafruit_NeoPixel strip) {
  uint16_t wait = 100;
  uint16_t i, j;
  while(!read(wait)){
    for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
      for(i=0; i< strip.numPixels(); i++) {
        strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      }
      strip.show();
      if(read(wait)) return;
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(Adafruit_NeoPixel strip) {
  uint16_t wait = 100;
  while(!read(wait)){
    for (int8_t j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
      for (int8_t q=0; q < 2; q++) {
        for (uint16_t i=0; i < strip.numPixels(); i=i+2) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
        if(read(wait)) return;
        for (uint16_t i=0; i < strip.numPixels(); i=i+2) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
      }
    }
  }
}

void allOnWheel(Adafruit_NeoPixel strip) {
  uint16_t wait = 200;
  while(!read(wait)){
    for (int8_t j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
      for (uint16_t i=0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, Wheel( j % 255));    //turn every third pixel on
      }
      strip.show();
      if(read(wait)) return;
    }
    for(uint16_t i=0; i<strip.numPixels(); i++)
      strip.setPixelColor(i, strip.Color(0,0,0));
    strip.show();
  }
}

void apagar(Adafruit_NeoPixel &strip){
  for(uint16_t i=0; i<strip.numPixels(); i++)
    strip.setPixelColor(i, strip.Color(0,0,0));
  strip.show();
  if(read(2)) return;
}

#endif
