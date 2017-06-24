#include <Adafruit_NeoPixel.h>
#include <stdint.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(300-105, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripFront = Adafruit_NeoPixel(20, 4, NEO_GRB + NEO_KHZ800);

uint16_t Wait = 1;
uint32_t Tiempo;
bool ChangeMode = true;
bool Old8 = false;
bool Old7 = false;
bool Cambio = false;

//LISTENER
void assignPin(){
  for(int8_t i = 7; i<=12; i++){
    pinMode(i, INPUT);
  }
}

bool readChange(){
  if(digitalRead(8)){
    if(!Old8){
      Old8 = true;
      ChangeMode = !ChangeMode;
    }
  }else{
    Old8 = false;
  }

  bool ret = false;
  if(digitalRead(7)){
    if(!Old7){
      Old7 = true;
      ret = true;
    }
  }else{
    Old7 = false;
  }
  return Cambio = ret;
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


//MAIN
//EFECTOS
void (*efectos[])(Adafruit_NeoPixel strip) = {
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
const uint8_t lengthEfectos = 9;
uint8_t numEfecto = 0;

void setup() {
  //Serial.begin(9600);
  assignPin();
  strip.begin();
  strip.show();
  stripFront.begin();
  stripFront.show();
}

void loop() {
  for(Tiempo = 0; !Cambio && Tiempo < 3;){
    (*efectos[numEfecto])();
    if(ChangeMode)
      Tiempo++;
  }
  (numEfecto < lengthEfectos-1) ? numEfecto++ : numEfecto = 0;
  Cambio = false;
}
