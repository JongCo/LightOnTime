#include "RTClib.h"

#define RTC_MIN_PIXELNUM 13

class RTCModeManager {
  private:
    RTC_DS3231 rtc;
  public:
    RTCModeManager();
    void init();
    uint8_t getHours();
    Array<uint32_t, RTC_MIN_PIXELNUM> getMinutesToColorArray(
      uint32_t n0PlaceColor,
      uint32_t nPlaceColor,
      uint32_t dividerColor
    );
};