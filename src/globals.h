#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

enum botones {NOINPUT=0, UNO=1, DOS=2, TRES=3, CUATRO=4, CINCO=5};

enum colores {RED = 16711680, GREEN = 65280, BLUE = 255,
  REDGREEN = 16776960, REDBLUE = 16711935, GREENBLUE = 65535, WHITE = 8355711};

uint32_t colorArray[7] = {RED, GREEN, BLUE, REDGREEN, REDBLUE, GREENBLUE, WHITE};

Adafruit_NeoPixel stripFront = Adafruit_NeoPixel(78, 3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(300-105, 6, NEO_GRB + NEO_KHZ800);

const uint8_t lengthEfectos = 9;
uint8_t numEfecto = 0;

bool activado = false;
uint16_t wait = 1;
bool power = true;
bool change = false;
uint8_t ciclo = 3;
uint8_t colorFront = 6;

#endif
