#include "RTClib.h"

#define RTC_HOUR_PIXELNUM 12
#define RTC_MIN_PIXELNUM 13

class RTCModeManager {
  private:
    RTC_DS3231 rtc;
  public:
    RTCModeManager();
    void init();
    Array<uint32_t, RTC_HOUR_PIXELNUM> getHoursToColorArray(
      uint32_t hourColor,
      uint32_t offColor
    );
    Array<uint32_t, RTC_MIN_PIXELNUM> getMinutesToColorArray(
      uint32_t n0PlaceColor,
      uint32_t nPlaceColor,
      uint32_t dividerColor
    );
};