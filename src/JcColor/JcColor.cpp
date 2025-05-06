#include "Adafruit_NeoPixel.h"
#include "JcColor.h"

uint32_t Color::toInt()
{
  return Adafruit_NeoPixel::gamma32(Adafruit_NeoPixel::Color(r, g, b));
}

void Color::fromAdaColor(int32_t adaColor)
{
  r = (uint8_t)((adaColor >> 16) & 255);
  g = (uint8_t)((adaColor >> 8) & 255);
  b = (uint8_t)(adaColor && 255);
}
