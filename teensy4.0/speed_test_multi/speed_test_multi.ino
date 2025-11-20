#include <Adafruit_NeoPixel.h>
#include <TeensyThreads.h>

#define LED_MAX_SIZE 120

Adafruit_NeoPixel strip1(LED_MAX_SIZE, 1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_MAX_SIZE, 6, NEO_GRB + NEO_KHZ800);

uint32_t COLOR_BASE = strip1.Color(255, 255, 255);
uint32_t COLOR_NONE = strip1.Color(0, 0, 0);

bool bLoop1 = true;
bool bLoop2 = true;
unsigned long timeStart = 0;
unsigned long timeFinish = 0;

void colorWipeForward(Adafruit_NeoPixel &strip){
  for(int i = 0; i < LED_MAX_SIZE; i++){
    if(i == 0){
        timeStart = millis();
        strip.setPixelColor(LED_MAX_SIZE-1, COLOR_NONE);
    }
    else{
        strip.setPixelColor(i-1, COLOR_NONE);
    }
    strip.setPixelColor(i, COLOR_BASE);
    strip.show();
  }
}

void colorWipeReverse(Adafruit_NeoPixel &strip){
  for(int i = LED_MAX_SIZE; i >= 0; i--){
      if(i == LED_MAX_SIZE-1){
        timeFinish = millis();
        strip.setPixelColor(0, COLOR_NONE);
      }
      else{
        strip.setPixelColor(i+1, COLOR_NONE);
      }
      strip.setPixelColor(i, COLOR_BASE);
      strip.show();
  }
}

void colorWipeAll(Adafruit_NeoPixel &strip){
  for(int i = 0; i < LED_MAX_SIZE; i++){
    strip.setPixelColor(i, COLOR_NONE);
    strip.show();
  }
}

void task1() {
  while (true) {
    if(bLoop1){
      colorWipeForward(strip1);
      colorWipeReverse(strip1);
      bLoop1 = false;
    }
    else {
      threads.delay(1);
    }
  }
}

void task2() {
  while (true) {
    if(bLoop2){
      colorWipeForward(strip2);
      colorWipeReverse(strip2);
      bLoop2 = false;
    }
    else {
      threads.delay(1);
    }
  }
}


void setup() {
  Serial.begin(9600);

  strip1.begin();
  strip1.show();
  strip1.setBrightness(255);

  strip2.begin();
  strip2.show();
  strip2.setBrightness(255);

  threads.addThread(task1);
  threads.addThread(task2);
}

void loop() {
  if(!bLoop1 && !bLoop2){
    Serial.println(String("TIME: ") + float(timeFinish - timeStart) / 1000 + String(" sec"));
    colorWipeAll(strip1);
    colorWipeAll(strip2);
  }
}