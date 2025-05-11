#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "RTClib.h"
#include "Array.h"
#include "RTCModeManager/RTCModeManager.h"
#include "JcColor/JcColor.h"

#define NEOPIN 12
#define NUMPIXELS 60

const Color DIVIDER_COLOR = Color::HSV(49000, 255, 50);

Adafruit_NeoPixel neoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);

uint32_t colors[60];

RTCModeManager rtcModeManager;

bool isReverseMode = true;

void pushLeft(uint32_t *brights);
void setRandomColorArray();
void nextPixel(uint8_t* indexRef, bool isReverseMode);

void setup() {
  neoPixel.begin();
  neoPixel.show();
  neoPixel.setBrightness(255);

  //setRandomColorArray();

  Serial.begin(9600);

  rtcModeManager.init();
}

void loop() {
  neoPixel.clear();

  uint8_t pixelPlace;
  if (isReverseMode) {
    pixelPlace = NUMPIXELS-1;
  } else {
    pixelPlace = 0;
  }

  Array<Color, RTC_HOUR_PIXELNUM> hourPattern
    = rtcModeManager.getHoursToColorArray(
      Color::HSV(8000, 255, 255),
      Color::HSV(49000, 140, 20)
  );

  Array<Color, RTC_MIN_PIXELNUM> minutePattern 
    = rtcModeManager.getMinutesToColorArray(
      Color::HSV(1000, 130, 255),
      Color::HSV(1000, 130, 255),
      Color::HSV(0, 255, 30),
      Color::HSV(49000, 140, 20)
  );

  Array<Color, RTC_SEC_PIXELNUM> secondsPattern
    = rtcModeManager.getSecondsToColorArray(
      4000, 255, 255, Color::HSV(49000, 140, 20)
  ); 
  
  // divider
  neoPixel.setPixelColor(pixelPlace, DIVIDER_COLOR.toAdaColor());
  nextPixel(&pixelPlace, isReverseMode);

  // hours
  for (size_t i = 0; i < RTC_HOUR_PIXELNUM; i++) {
    neoPixel.setPixelColor(pixelPlace, hourPattern[i].toAdaColor());
    nextPixel(&pixelPlace, isReverseMode);
  }

  // divider
  neoPixel.setPixelColor(pixelPlace, DIVIDER_COLOR.toAdaColor());
  nextPixel(&pixelPlace, isReverseMode);
  // divider
  neoPixel.setPixelColor(pixelPlace, DIVIDER_COLOR.toAdaColor());
  nextPixel(&pixelPlace, isReverseMode);

  // minutes
  for (size_t i = 0; i < RTC_MIN_PIXELNUM; i++) {
    neoPixel.setPixelColor(pixelPlace, minutePattern[i].toAdaColor());
    nextPixel(&pixelPlace, isReverseMode);
  }

  // divider
  neoPixel.setPixelColor(pixelPlace, DIVIDER_COLOR.toAdaColor());
  nextPixel(&pixelPlace, isReverseMode);
  // divider
  neoPixel.setPixelColor(pixelPlace, DIVIDER_COLOR.toAdaColor());
  nextPixel(&pixelPlace, isReverseMode);

  // seconds
  for (size_t i = 0; i < RTC_SEC_PIXELNUM; i++) {
    neoPixel.setPixelColor(pixelPlace, secondsPattern[i].toAdaColor());
    nextPixel(&pixelPlace, isReverseMode);
  }

  // divider
  neoPixel.setPixelColor(pixelPlace, DIVIDER_COLOR.toAdaColor());
  nextPixel(&pixelPlace, isReverseMode);

  neoPixel.show();

  delay(50);
}

void pushLeft(uint32_t* target) {
  uint32_t firstValue = target[0];

  for (int i = 0; i < NUMPIXELS -1 ; i++) {
    target[i] = target[i+1];
  }

  target[NUMPIXELS - 1] = firstValue;
}

void setRandomColorArray() {
  for (int i = 0; i < NUMPIXELS; i++) {
    colors[i] = Adafruit_NeoPixel::ColorHSV(random(1000, 8000), 255, 255);
  }
}

void nextPixel(uint8_t* indexRef, bool isReverseMode) {
  if (isReverseMode) {
    *indexRef = *indexRef-1;
  } else {
    *indexRef = *indexRef+1;
  }
}