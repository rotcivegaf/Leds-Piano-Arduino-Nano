#ifndef MODOS_H
#define MODOS_H

#define RED       16711680
#define GREEN     65280
#define BLUE      255
#define REDGREEN  16776960
#define REDBLUE   16711935
#define GREENBLUE 65535
#define WHITE     8355711

//EFECTOS
void colorWipe() {
  Wait = 1;
  uint32_t c[7] = {RED, GREEN, BLUE, REDGREEN, REDBLUE, GREENBLUE, WHITE};

  for(uint8_t j = 0; j<7; j++){
    for(uint16_t i=0; i<Strip.numPixels(); i++) {
      Strip.setPixelColor(i, c[j]);
      Strip.show();
      if(waitListen()) return;
    }
  }
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

void colorWipeComb(){
  Wait = 5;
  uint32_t c1 = 0, c2 = 0;

  while(c1==c2) {
    c1 = getColor(random(0,6));
    c2 = getColor(random(0,6));
  }
  for(uint16_t j=Strip.numPixels()-1, i=0; i < Strip.numPixels(); i++, j--) {
    Strip.setPixelColor(j, c1);
    Strip.setPixelColor(i, c2);
    Strip.show();
    if(waitListen()) return;
  }
}

void colorWipeComb4() {
  Wait = 5;
  uint32_t c1 = 0, c2 = 0, c3, c4;
  while(c1==c2) {
    c1 = REDGREEN;
    c2 = REDBLUE;
    c3 = GREENBLUE;
    c4 = GREEN;
  }
  uint16_t i = 0;
  uint16_t j = Strip.numPixels()/4;
  uint16_t k = Strip.numPixels()/2;
  uint16_t l = Strip.numPixels()*3/4;

  for(; i < Strip.numPixels(); i++, j++, k++, l++) {
    if(j >= Strip.numPixels()-1){
      j = 0;
    }
    if(k >= Strip.numPixels()-1){
      k = 0;
    }
    if(l >= Strip.numPixels()-1){
      l = 0;
    }

    Strip.setPixelColor(i, c1);
    Strip.setPixelColor(j, c2);
    Strip.setPixelColor(k, c3);
    Strip.setPixelColor(l, c4);

    Strip.show();
    if(waitListen()) return;
  }

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
void theaterChase() {
  Wait = 300;
  uint32_t c[7] = {RED, GREEN, BLUE, REDGREEN, REDBLUE, GREENBLUE, WHITE};

  while(1){
    for(uint8_t j = 0; j<7; j++){
      for(uint8_t e = 0; e<10; e++){
        for (int8_t q=0; q < 3; q++) {
          for (uint16_t i=0; i < Strip.numPixels(); i=i+3) {
            Strip.setPixelColor(i+q, c[j]);    //turn every third pixel on
          }
          Strip.show();
          if(waitListen()) return;

          for (uint16_t i=0; i < Strip.numPixels(); i=i+3) {
            Strip.setPixelColor(i+q, 0);        //turn every third pixel off
          }
        }
      }
    }
  }
}

void randomLeds() {
  Wait = 100;
  for(uint16_t i=0; i<Strip.numPixels(); i++){
    Strip.setPixelColor(random(0, Strip.numPixels()), 0);
    Strip.setPixelColor(random(0, Strip.numPixels()), random(0, 16777215));
    Strip.show();
    if(waitListen()) return;
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
      Strip.show();
      if(waitListen()) return;
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
      Strip.show();
      if(waitListen()) return;
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
        Strip.show();
        if(waitListen()) return;
        for (uint16_t i=0; i < Strip.numPixels(); i=i+2) {
          Strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
      }
    }
  }
}

void allOnWheel() {
  Wait = 200;
  while(!listen()){
    for (int8_t j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
      for (uint16_t i=0; i < Strip.numPixels(); i++) {
        Strip.setPixelColor(i, Wheel( j % 255));    //turn every third pixel on
      }
      Strip.show();
      if(waitListen()) return;
    }


    for(uint16_t i=0; i<Strip.numPixels(); i++)
      Strip.setPixelColor(i, Strip.Color(0,0,0));
    Strip.show();
delay(10000);

  }
}

void apagar(){
    for(uint16_t i=0; i<Strip.numPixels(); i++)
      Strip.setPixelColor(i, Strip.Color(0,0,0));
    Strip.show();
    if(waitListen()) return;

}

#endif
