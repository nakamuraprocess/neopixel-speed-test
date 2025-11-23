#include <Adafruit_NeoPixel.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"

#define LED_MAX_SIZE 120

Adafruit_NeoPixel strip1(LED_MAX_SIZE, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_MAX_SIZE, 3, NEO_GRB + NEO_KHZ800);

uint32_t COLOR_BASE = strip1.Color(255, 255, 255);
uint32_t COLOR_NONE = strip1.Color(0, 0, 0);

bool bLoop = true;
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
    delay(1);
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
    delay(1);
  }
}

void colorWipeAll(Adafruit_NeoPixel &strip){
  for(int i = 0; i < LED_MAX_SIZE; i++){
    strip.setPixelColor(i, COLOR_NONE);
    strip.show();
  }
}

void core1_task() {
  colorWipeForward(strip2);
  colorWipeReverse(strip2);
  colorWipeAll(strip2);
}

void setup() {
  Serial.begin(9600);
  
  strip1.begin();
  strip1.show();
  strip1.setBrightness(255);

  strip2.begin();
  strip2.show();
  strip2.setBrightness(255);

  multicore_launch_core1(core1_task);
}

void loop() {
  if(bLoop){
    colorWipeForward(strip1);
    colorWipeReverse(strip1);
    colorWipeAll(strip1);
    bLoop = false;
  }
  if(timeFinish > 0.0 && timeStart > 0.0){
    Serial.println(String("TIME: ") + float(timeFinish - timeStart) / 1000 + String(" sec"));
  }
}