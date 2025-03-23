#include "Arduino.h"
#include "RTClib.h"
#include "Array.h"
#include "Adafruit_NeoPixel.h"
#include "RTCModeManager.h"

RTCModeManager::RTCModeManager() {

}

void RTCModeManager::init()
{
  rtc.begin();
}

uint8_t RTCModeManager::getHours() {
  return rtc.now().hour();
}

/**
 * @brief Returns the current minutes as an array of Adafruit_NeoPixel::Color
 * 
 * xxxDnnnnnnnnn (x : tens place(binary), D : divider, n : ones place)
 * 
 * @return An array of uint32_t representing the current minute
 */
Array<uint32_t, RTC_MIN_PIXELNUM> RTCModeManager::getMinutesToColorArray(
  uint32_t n0PlaceColor,
  uint32_t nPlaceColor,
  uint32_t dividerColor
) {

  Array<uint32_t, RTC_MIN_PIXELNUM> colorArray;
  colorArray = {0};

  uint8_t minute = rtc.now().minute();
  uint8_t n0Digit = minute/10;
  uint8_t nDigit = minute%10;

  for (int i = 0; i < 3; i++) {
    if ( n0Digit >> i & 1 ) {
      colorArray[2-i] = n0PlaceColor;
    } else {
      colorArray[2-i] = Adafruit_NeoPixel::ColorHSV(0, 0, 0);
    }
  }

  colorArray[3] = dividerColor;

  for (int i = 0; i < nDigit; i++) {
    colorArray[(RTC_MIN_PIXELNUM-1)-i] = nPlaceColor;
  }

  return colorArray;
}