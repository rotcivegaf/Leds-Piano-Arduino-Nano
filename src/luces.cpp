#include <Adafruit_NeoPixel.h>
#include <stdint.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define RED       16711680
#define GREEN     65280
#define BLUE      255
#define REDGREEN  16776960
#define REDBLUE   16711935
#define GREENBLUE 65535
#define WHITE     8355711

Adafruit_NeoPixel Strip = Adafruit_NeoPixel(300, 6, NEO_GRB + NEO_KHZ800);
uint16_t Wait = 1;
uint8_t Mode = 0;
uint8_t Old8 = 0;
uint8_t Old7 = 0;
uint8_t ModeMax = 10;

//LISTENER
void assignPin(){
  for(int8_t i = 7; i<=12; i++){
    pinMode(i, INPUT);
  }
}

bool readChange(){
  bool ret = false;
  if(digitalRead(7)){
    if(!Old7){
      if(Mode < ModeMax)
        Mode++;
      else
        Mode = 0;
      Old7 = 1;
      ret = true;
    }
  }else{
    Old7 = 0;
  }
  if(digitalRead(8)){
    if(!Old8){
      if(Mode > 0)
        Mode--;
      else
        Mode = ModeMax;
      Old8 = 1;
      ret = true;
    }
  }else{
    Old8 = 0;
  }
  return ret;
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

//STRIP
void apagar(){
  for(uint16_t i=0; i<Strip.numPixels(); i++)
    Strip.setPixelColor(i, Strip.Color(0,0,0));
  Strip.show();
}

bool colorWipe(uint32_t c) {
  Wait = 10;
  for(uint16_t j=Strip.numPixels()-1, i=0; j>i; i++, j--) {
    if(waitListen())
      return true;

    Strip.setPixelColor(j, c);
    Strip.setPixelColor(i, c);
    Strip.show();
  }

  return false;
}

uint32_t getColor(uint8_t x){
  if(x == 0)
    return RED;
  if(x == 1)
    return GREEN;
  if(x == 2)
    return BLUE;
  if(x == 3)
    return REDBLUE;
  if(x == 4)
    return REDGREEN;
  if(x == 5)
    return GREENBLUE;
  return WHITE;
}

bool colorWipeComb() {
  Wait = 5;
  uint32_t c1 = 0, c2 = 0;
  while(c1==c2) {
    c1 = getColor(random(0,6));
    c2 = getColor(random(0,6));
  }
  for(uint16_t j=Strip.numPixels()-1, i=0; i < Strip.numPixels(); i++, j--) {
    if(waitListen())
      return true;

    Strip.setPixelColor(j, c1);
    Strip.setPixelColor(i, c2);
    Strip.show();
  }

  return false;
}
/*
void allChange(){
  uint32_t auxC, c1 = 0, c2 = 0;
  uint16_t i;
  while(!listen()){
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
      for(i=0; i< Strip.numPixels(); i++) {
        Strip.setPixelColor(i, c1);
      }
      if(listen())
        return;

      Strip.show();
      delay(1);
    }
  }
}*/

//Theatre-style crawling lights.
void theaterChase(uint32_t c) {
  Wait = 100;
  while(!listen()){
    for (int8_t q=0; q < 3; q++) {
      for (uint16_t i=0; i < Strip.numPixels(); i=i+3) {
        Strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      Strip.show();
      if(waitListen())
        return;

      for (uint16_t i=0; i < Strip.numPixels(); i=i+3) {
        Strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}


void randomLeds() {
  Wait = 100;
  while(!listen()){
    if(waitListen())
      return;
    Strip.setPixelColor(random(0, Strip.numPixels()), 0);
    Strip.setPixelColor(random(0, Strip.numPixels()), random(0, 16777215));
    Strip.show();
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return Strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return Strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return Strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rainbow() {
  Wait = 100;
  uint16_t i, j;
  while(!listen()){
    for(j=0; j<256; j++) {
      for(i=0; i<Strip.numPixels(); i++) {
        Strip.setPixelColor(i, Wheel((i+j) & 255));
      }
      if(waitListen())
        return;
      Strip.show();
    }
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle() {
  Wait = 100;
  uint16_t i, j;
  while(!listen()){
    for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
      for(i=0; i< Strip.numPixels(); i++) {
        Strip.setPixelColor(i, Wheel(((i * 256 / Strip.numPixels()) + j) & 255));
      }
      if(waitListen())
        return;
      Strip.show();
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow() {
  Wait = 100;
  while(!listen()){
    for (int8_t j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
      for (int8_t q=0; q < 2; q++) {
        for (uint16_t i=0; i < Strip.numPixels(); i=i+2) {
          Strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        if(waitListen())
          return;
        Strip.show();
        for (uint16_t i=0; i < Strip.numPixels(); i=i+2) {
          Strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
      }
    }
  }
}


//MAIN
void setup() {
  //Serial.begin(9600);
  assignPin();
  Strip.begin();
  Strip.show();
}

void loop() {
  listen();
  switch (Mode) {
    case 0:
      break;
    case 1:
      randomLeds();
      break;
    case 2:
      while(1){
        if(colorWipe(RED) || colorWipe(GREEN) || colorWipe(BLUE) || colorWipe(WHITE))
          break;
      }
      break;
    case 3:
      while(1){
        if(colorWipeComb())
          break;
      }
      break;
    case 4:
      theaterChase(WHITE);
      break;
    case 5:
      theaterChase(RED);
      break;
    case 6:
      theaterChase(BLUE);
      break;
    case 7:
      theaterChase(GREEN);
      break;
    case 8:
      rainbow();
      break;
    case 9:
      rainbowCycle();
      break;
    case 10:
      theaterChaseRainbow();
      break;
  /*  case 11:
      allChange();
      break;*/
  }
  apagar();
}
