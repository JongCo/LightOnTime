#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "RTClib.h"
#include "Array.h"
#include "rtcManager/RTCModeManager.h"

#define NEOPIN 12
#define NUMPIXELS 60

Adafruit_NeoPixel neoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);

uint32_t colors[60];

RTCModeManager rtcModeManager;

void pushLeft(uint32_t *brights);
void setRandomColorArray();

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

  uint8_t pixelPlace = 0;

  Array<uint32_t, RTC_HOUR_PIXELNUM> hourPattern
    = rtcModeManager.getHoursToColorArray(
      Adafruit_NeoPixel::ColorHSV(4000, 255, 255),
      Adafruit_NeoPixel::ColorHSV(49000, 140, 20)
  );

  Array<uint32_t, RTC_MIN_PIXELNUM> minutePattern 
    = rtcModeManager.getMinutesToColorArray(
      Adafruit_NeoPixel::ColorHSV(1000, 220, 255),
      Adafruit_NeoPixel::ColorHSV(1000, 220, 255),
      Adafruit_NeoPixel::ColorHSV(0, 255, 30),
      Adafruit_NeoPixel::ColorHSV(49000, 140, 20)
  );

  Array<uint32_t, RTC_SEC_PIXELNUM> secondsPattern
    = rtcModeManager.getSecondsToColorArray(
      1000, 255, 255,
      Adafruit_NeoPixel::ColorHSV(49000, 140, 20)
  );
  
  // divider
  neoPixel.setPixelColor(pixelPlace, Adafruit_NeoPixel::ColorHSV(16000, 255, 50));
  pixelPlace++;

  // hours
  for (size_t i = 0; i < RTC_HOUR_PIXELNUM; i++) {
    neoPixel.setPixelColor(pixelPlace, hourPattern[i]);
    pixelPlace++;
  }

  // divider
  neoPixel.setPixelColor(pixelPlace, Adafruit_NeoPixel::ColorHSV(16000, 255, 50));
  pixelPlace++;
  // divider
  neoPixel.setPixelColor(pixelPlace, Adafruit_NeoPixel::ColorHSV(16000, 255, 50));
  pixelPlace++;

  // minutes
  for (size_t i = 0; i < RTC_MIN_PIXELNUM; i++) {
    neoPixel.setPixelColor(pixelPlace, minutePattern[i]);
    pixelPlace++;
  }

  // divider
  neoPixel.setPixelColor(pixelPlace, Adafruit_NeoPixel::ColorHSV(16000, 255, 50));
  pixelPlace++;
  // divider
  neoPixel.setPixelColor(pixelPlace, Adafruit_NeoPixel::ColorHSV(16000, 255, 50));
  pixelPlace++;

  // seconds
  for (size_t i = 0; i < RTC_SEC_PIXELNUM; i++) {
    neoPixel.setPixelColor(pixelPlace, secondsPattern[i]);
    pixelPlace++;
  }

  // divider
  neoPixel.setPixelColor(pixelPlace, Adafruit_NeoPixel::ColorHSV(16000, 255, 50));
  pixelPlace++;

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