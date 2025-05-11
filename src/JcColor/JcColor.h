#include "Arduino.h"

struct Color{
  uint8_t r;
  uint8_t g;
  uint8_t b;

  static Color RGB(uint8_t r, uint8_t g, uint8_t b);
  static Color AdaColor(int32_t adaColor);
  static Color HSV(uint16_t hue, int8_t saturation, int8_t value);

  uint32_t toAdaColor();
  void fromAdaColor(uint32_t adaColor);
  void fromHSV(int16_t hue, int8_t saturation, int8_t value);
};