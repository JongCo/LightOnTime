#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "RTClib.h"
#include "Array.h"
#include "RTCModeManager/RTCModeManager.h"
#include "JcColor/JcColor.h"
#include "Button/Button.h"

#define NEOPIN 12
#define NUMPIXELS 60

#define DELAY_MILIES 16

const Color DIVIDER_COLOR = Color::FromHSV(16000, 255, 127);

Adafruit_NeoPixel neoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);

Color colors[60];
Color targetColors[60];

RTCModeManager rtcModeManager;
Button button;

bool isReverseMode = true;

void nextPixel(uint8_t* indexRef, bool isReverseMode);
void transitColor(Color* currentColors, Color* targetColors);

// brightnessControl
uint8_t brightnessMode = 0;
float brightnessModeValues[] = {1.0f, 0.8f, 0.6f, 0.4f};

void setup() {
  neoPixel.begin();
  neoPixel.show();
  neoPixel.setBrightness(255);

  //setRandomColorArray();

  Serial.begin(9600);

  rtcModeManager.init();
  button.start({{8, 255, 255, 255, 255, 255, 255, 255}});
}

void loop() {
  button.update();
  if(button.getButtonDown(0)) {
    brightnessMode++;
    brightnessMode = brightnessMode >= 4 ? 0 : brightnessMode;
  }
  
  neoPixel.clear();

  uint8_t pixelPlace;
  if (isReverseMode) {
    pixelPlace = NUMPIXELS-1;
  } else {
    pixelPlace = 0;
  }

  Array<Color, RTC_HOUR_PIXELNUM> hourPattern
    = rtcModeManager.getHoursToColorArray(
      Color::FromHSV(8000, 255, 255),
      Color::FromHSV(49000, 190, 120)
  );

  Array<Color, RTC_MIN_PIXELNUM> minutePattern 
    = rtcModeManager.getMinutesToColorArray(
      Color::FromHSV(1000, 130, 255),
      Color::FromHSV(1000, 130, 255),
      Color::FromHSV(0, 255, 100),
      Color::FromHSV(49000, 190, 120)
  );

  Array<Color, RTC_SEC_PIXELNUM> secondsPattern
    = rtcModeManager.getSecondsToColorArray(
      4000, 255, 255, Color::FromHSV(49000, 190, 120)
  ); 
  
  // divider
  targetColors[pixelPlace] = DIVIDER_COLOR;
  nextPixel(&pixelPlace, isReverseMode);

  // hours
  for (size_t i = 0; i < RTC_HOUR_PIXELNUM; i++) {
    targetColors[pixelPlace] = hourPattern[i];
    nextPixel(&pixelPlace, isReverseMode);
  }

  // divider
  targetColors[pixelPlace] = DIVIDER_COLOR;
  nextPixel(&pixelPlace, isReverseMode);
  // divider
  targetColors[pixelPlace] = DIVIDER_COLOR;
  nextPixel(&pixelPlace, isReverseMode);

  // minutes
  for (size_t i = 0; i < RTC_MIN_PIXELNUM; i++) {
    targetColors[pixelPlace] = minutePattern[i];
    nextPixel(&pixelPlace, isReverseMode);
  }

  // divider
  targetColors[pixelPlace] = DIVIDER_COLOR;
  nextPixel(&pixelPlace, isReverseMode);
  // divider
  targetColors[pixelPlace] = DIVIDER_COLOR;
  nextPixel(&pixelPlace, isReverseMode);

  // seconds
  for (size_t i = 0; i < RTC_SEC_PIXELNUM; i++) {
    // neoPixel.setPixelColor(pixelPlace, secondsPattern[i].toAdaColor());
    targetColors[pixelPlace] = secondsPattern[i];
    nextPixel(&pixelPlace, isReverseMode);
  }

  // divider
  targetColors[pixelPlace] = DIVIDER_COLOR;
  nextPixel(&pixelPlace, isReverseMode);

  // brightnessControl
  for (size_t i = 0; i < NUMPIXELS; i++) {
    targetColors[i] = targetColors[i] * brightnessModeValues[brightnessMode];
  }

  transitColor(colors, targetColors);
  for (size_t i = 0; i < NUMPIXELS; i++) {
    neoPixel.setPixelColor(i, colors[i].toAdaColor());
  }
  neoPixel.show();

  delay(DELAY_MILIES);
}

void nextPixel(uint8_t* indexRef, bool isReverseMode) {
  if (isReverseMode) {
    *indexRef = *indexRef-1;
  } else {
    *indexRef = *indexRef+1;
  }
}

void transitColor(Color *currentColors, Color *targetColors)
{
  for(size_t i = 0; i < NUMPIXELS; i++) {
    currentColors[i] = Color::lerp(currentColors[i], targetColors[i], 0.05f);
  }
}
