#include "Arduino.h"

struct Color{
  uint8_t r;
  uint8_t g;
  uint8_t b;

  uint32_t toAdaColor();
  void fromAdaColor(int32_t adaColor);
  void fromHSV(int16_t hue, int8_t saturation, int8_t value);
};