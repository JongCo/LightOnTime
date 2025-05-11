#include "RTClib.h"
#include "JcColor/JcColor.h"

#define RTC_HOUR_PIXELNUM 12
#define RTC_MIN_PIXELNUM 13
#define RTC_SEC_PIXELNUM 6

class RTCModeManager {
  private:
    RTC_DS3231 rtc;
  public:
    RTCModeManager();
    void init();
    Array<Color, RTC_HOUR_PIXELNUM> getHoursToColorArray(
      Color hourColor,
      Color offColor
    );
    Array<Color, RTC_MIN_PIXELNUM> getMinutesToColorArray(
      Color n0PlaceColor,
      Color nPlaceColor,
      Color dividerColor,
      Color offColor
    );
    Array<Color, RTC_SEC_PIXELNUM> getSecondsToColorArray(
      uint16_t hue,
      uint8_t saturation,
      uint8_t colorValue,
      Color offColor
    );
};