#include "Arduino.h"
#include "RTClib.h"
#include "Array.h"
#include "Adafruit_NeoPixel.h"
#include "JcColor/JcColor.h"
#include "RTCModeManager.h"

RTCModeManager::RTCModeManager() {

}

void RTCModeManager::init()
{
  rtc.begin();
}

Array<uint32_t, RTC_HOUR_PIXELNUM> RTCModeManager::getHoursToColorArray(
  uint32_t hourColor,
  uint32_t offColor
) {
  
  
  Array<uint32_t, RTC_HOUR_PIXELNUM> colorArray;
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
 * @brief Returns the current minutes as an array of Adafruit_NeoPixel::Color
 * 
 * xxxDnnnnnnnnn (x : tens place(binary), D : divider, n : ones place)
 * 
 * @return An array of uint32_t representing the current minute
 */
Array<uint32_t, RTC_MIN_PIXELNUM> RTCModeManager::getMinutesToColorArray(
  uint32_t n0PlaceColor,
  uint32_t nPlaceColor,
  uint32_t dividerColor,
  uint32_t offColor
) {

  Array<uint32_t, RTC_MIN_PIXELNUM> colorArray;
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

Array<uint32_t, RTC_SEC_PIXELNUM> RTCModeManager::getSecondsToColorArray(
  uint16_t hue,
  uint8_t saturation,
  uint8_t colorValue,
  uint32_t offColor
) {
  Array<uint32_t, RTC_SEC_PIXELNUM> colorArray;
  colorArray = {offColor};

  uint8_t seconds = rtc.now().second();
  uint8_t place = seconds/10 + 1;
  uint8_t value = seconds%10;

  for (int i = 0; i < place; i++) {
    if (i == place-1) {
      colorArray[(RTC_SEC_PIXELNUM-1)-i] 
        = Adafruit_NeoPixel::ColorHSV(hue, saturation, colorValue * (value/10.0f));
    } else {
      colorArray[(RTC_SEC_PIXELNUM-1)-i]
        = Adafruit_NeoPixel::ColorHSV(hue, saturation, colorValue);
    }
  }

  return colorArray;
}

Array<Color, RTC_SEC_PIXELNUM> RTCModeManager::getSecondsToJcColorArray(
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
      Color secColor;
      secColor.fromHSV(hue, saturation, colorValue * (value/10.0f));
      colorArray[(RTC_SEC_PIXELNUM-1)-i] = secColor;
    } else {
      Color secColor;
      secColor.fromHSV(hue, saturation, colorValue);
      colorArray[(RTC_SEC_PIXELNUM-1)-i] = secColor;
    }
  }

  return colorArray;
}
