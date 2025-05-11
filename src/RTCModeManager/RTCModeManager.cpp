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

Array<Color, RTC_HOUR_PIXELNUM> RTCModeManager::getHoursToColorArray(
  Color hourColor,
  Color offColor
) {

  Array<Color, RTC_HOUR_PIXELNUM> colorArray;
  colorArray = {offColor};
  
  uint8_t hour = rtc.now().hour();

  bool isPM = hour >= 12;
  hour = isPM ? hour - 12 : hour;
  

  for (int i = 0; i < hour; i++) {
    colorArray[(RTC_HOUR_PIXELNUM-1)-i] = hourColor;
  }

  return colorArray;
}

/**
 * @brief Returns the current minutes as an array of Color
 * 
 * xxxDnnnnnnnnn (x : tens place(binary), D : divider, n : ones place)
 * 
 * @return An array of Color representing the current minute
 */
Array<Color, RTC_MIN_PIXELNUM> RTCModeManager::getMinutesToColorArray(
  Color n0PlaceColor,
  Color nPlaceColor,
  Color dividerColor,
  Color offColor
) {

  Array<Color, RTC_MIN_PIXELNUM> colorArray;
  colorArray = {offColor};

  uint8_t minute = rtc.now().minute();
  uint8_t n0Digit = minute/10;
  uint8_t nDigit = minute%10;

  for (int i = 0; i < 3; i++) {
    if ( n0Digit >> i & 1 ) {
      colorArray[2-i] = n0PlaceColor;
    } else {
      colorArray[2-i] = offColor;
    }
  }

  colorArray[3] = dividerColor;

  for (int i = 0; i < nDigit; i++) {
    colorArray[(RTC_MIN_PIXELNUM-1)-i] = nPlaceColor;
  }

  return colorArray;
}

Array<Color, RTC_SEC_PIXELNUM> RTCModeManager::getSecondsToColorArray(
  uint16_t hue, 
  uint8_t saturation,
  uint8_t colorValue,
  Color offColor
) {
  Array<Color, RTC_SEC_PIXELNUM> colorArray;
  colorArray = {offColor};

  uint8_t seconds = rtc.now().second();
  uint8_t place = seconds/10 + 1;
  uint8_t value = seconds%10;

  for (int i = 0; i < place; i++) {
    if (i == place-1) {
      colorArray[(RTC_SEC_PIXELNUM-1)-i] = Color::HSV(hue, saturation, colorValue * (value/10.0f));
    } else {
      colorArray[(RTC_SEC_PIXELNUM-1)-i] = Color::HSV(hue, saturation, colorValue);
    }
  }

  return colorArray;
}
