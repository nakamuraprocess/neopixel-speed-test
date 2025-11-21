#include <FastLED.h>
#include <TeensyThreads.h>

#define LED_MAX_SIZE 120
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

CRGB strip1[LED_MAX_SIZE];
CRGB strip2[LED_MAX_SIZE];

bool bLoop1 = true;
bool bLoop2 = true;
unsigned long timeStart = 0;
unsigned long timeFinish = 0;

void tread1(){
  if(bLoop1){
    for (int i = 0; i < LED_MAX_SIZE; i++) {
      if(i == 0){
        timeStart = millis();
        strip2[LED_MAX_SIZE-1] =  CRGB::Black;
      }
      else{
        strip2[i-1] = CRGB::Black;
      }
      strip2[i] = CRGB::White;
      FastLED.show();
      //threads.delay(1);
    }
    for (int i = LED_MAX_SIZE - 1; i >= 0; i--) {
      if(i == LED_MAX_SIZE-1){
        timeFinish = millis();
        strip2[0] = CRGB::Black;
      }
      else{
        strip2[i+1] = CRGB::Black;
      }
      strip2[i] = CRGB::White;
      FastLED.show();
      //threads.delay(1);
    }
    bLoop1 = false;
  }
}

void setup() {
  FastLED.addLeds<LED_TYPE, 1, GRB>(strip1, LED_MAX_SIZE);
  FastLED.addLeds<LED_TYPE, 6, GRB>(strip2, LED_MAX_SIZE);
  FastLED.setBrightness(255);

  threads.addThread(tread1);
}

void loop() {
  if(bLoop1){
    for (int i = 0; i < LED_MAX_SIZE; i++) {
      if(i == 0){
        timeStart = millis();
        strip1[LED_MAX_SIZE-1] =  CRGB::Black;
      }
      else{
        strip1[i-1] = CRGB::Black;
      }
      strip1[i] = CRGB::White;
      FastLED.show();
      delay(1);
    }
    for (int i = LED_MAX_SIZE - 1; i >= 0; i--) {
      if(i == LED_MAX_SIZE-1){
        timeFinish = millis();
        strip1[0] = CRGB::Black;
      }
      else{
        strip1[i+1] = CRGB::Black;
      }
      strip1[i] = CRGB::White;
      FastLED.show();
      delay(1);
    }
    bLoop1 = false;
  }
  else {
    FastLED.clear();
    FastLED.show();
    delay(1);
  }
  if(timeFinish > 0.0 && timeStart > 0.0){
    Serial.println(String("TIME: ") + float(timeFinish - timeStart) / 1000 + String(" sec"));
  }
}