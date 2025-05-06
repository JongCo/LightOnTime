#include "Arduino.h"

struct Color{
  uint8_t r;
  uint8_t g;
  uint8_t b;

  uint32_t toInt();
  void fromAdaColor(int32_t adaColor);
};