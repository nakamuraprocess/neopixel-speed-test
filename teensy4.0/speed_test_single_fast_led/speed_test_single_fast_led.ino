#include <FastLED.h>

#define LED_PIN 6
#define LED_MAX_SIZE 120
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

CRGB leds[LED_MAX_SIZE];

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, LED_MAX_SIZE);
  FastLED.setBrightness(255);
}

void loop() {
  for (int i = 0; i < LED_MAX_SIZE; i++) {
    if(i == 0){
      leds[LED_MAX_SIZE-1] =  CRGB::Black;
    }
    else{
      leds[i-1] =  CRGB::Black;
    }
    leds[i] = CRGB::White;
    FastLED.show();
    delay(1);
  }

  for (int i = LED_MAX_SIZE - 1; i >= 0; i--) {
    if(i == LED_MAX_SIZE-1){
      leds[0] = CRGB::Black;
    }
    else{
      leds[i+1] = CRGB::Black;
    }
    leds[i] = CRGB::White;
    FastLED.show();
    delay(1);
  }
}