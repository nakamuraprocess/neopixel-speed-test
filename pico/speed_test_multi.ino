#include <Adafruit_NeoPixel.h>

#define LED_MAX_SIZE 120

Adafruit_NeoPixel strip1(LED_MAX_SIZE, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_MAX_SIZE, 3, NEO_GRB + NEO_KHZ800);

uint32_t COLOR_BASE = strip1.Color(255, 255, 255);
uint32_t COLOR_NONE = strip1.Color(0, 0, 0);

void colorWipeForward(Adafruit_NeoPixel &strip){
  for(int i = 0; i < LED_MAX_SIZE; i++){
    if(i == 0){
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


void setup() {
  strip1.begin();
  strip1.show();
  strip1.setBrightness(255);

  strip2.begin();
  strip2.show();
  strip2.setBrightness(255);
}

void loop() {
  colorWipeForward(strip1);
  colorWipeReverse(strip1);
  colorWipeForward(strip2);
  colorWipeReverse(strip2);
}