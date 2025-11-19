#include <Adafruit_NeoPixel.h>

#define LED_MAX_SIZE 120

Adafruit_NeoPixel strip1(LED_MAX_SIZE, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_MAX_SIZE, 15, NEO_GRB + NEO_KHZ800);

uint32_t COLOR_BASE = strip1.Color(255, 255, 255);
uint32_t COLOR_NONE = strip1.Color(0, 0, 0);

TaskHandle_t Task1_handle;
TaskHandle_t Task2_handle;

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

void task1(void *pvParameters) {
  while (true) {
    if(bLoop1){
      colorWipeForward(strip1);
      colorWipeReverse(strip1);
      bLoop1 = false;
    }
    else {
      vTaskDelay(1);
    }
  }
}

void task2(void *pvParameters) {
  while (true) {
    if(bLoop2){
      colorWipeForward(strip2);
      colorWipeReverse(strip2);
      bLoop2 = false;
    }
    else {
      vTaskDelay(1);
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

  xTaskCreatePinnedToCore(task1, "Task1", 4000, NULL, 6, &Task1_handle, 0);
  xTaskCreatePinnedToCore(task2, "Task2", 4000, NULL, 6, &Task2_handle, 1);
}

void loop() {
  if(!bLoop1 && !bLoop2){
    Serial.println(String("TIME: ") + float(timeFinish - timeStart) / 1000 + String(" sec"));
    colorWipeAll(strip1);
    colorWipeAll(strip2);
  }
}