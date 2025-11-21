#include <FastLED.h>

#define LED_PIN 6
#define LED_MAX_SIZE 120
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

CRGB leds[LED_MAX_SIZE];

bool bLoop = true;
unsigned long timeStart = 0;
unsigned long timeFinish = 0;

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, LED_MAX_SIZE);
  FastLED.setBrightness(255);
}

void loop() {
  if(bLoop){
    for (int i = 0; i < LED_MAX_SIZE; i++) {
      if(i == 0){
        timeStart = millis();
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
        timeFinish = millis();
        leds[0] = CRGB::Black;
      }
      else{
        leds[i+1] = CRGB::Black;
      }
      leds[i] = CRGB::White;
      FastLED.show();
      delay(1);
    }
    bLoop = false;
  }
  else {
    for (int i = 0; i < LED_MAX_SIZE; i++) {
      leds[i] = CRGB::Black;
      FastLED.show();
      delay(1);
    }
  }
  if(timeFinish > 0.0 && timeStart > 0.0){
    Serial.println(String("TIME: ") + float(timeFinish - timeStart) / 1000 + String(" sec"));
  }
}