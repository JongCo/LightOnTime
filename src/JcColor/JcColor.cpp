#include "Adafruit_NeoPixel.h"
#include "JcColor.h"

Color Color::RGB(uint8_t r, uint8_t g, uint8_t b)
{
  Color color;
  color.r = r;
  color.g = g;
  color.b = b;
  return color;
}

Color Color::AdaColor(int32_t adaColor)
{
  Color color;
  color.fromAdaColor(adaColor);
  return color;
}

Color Color::HSV(uint16_t hue, int8_t saturation, int8_t value)
{
  Color color;
  color.fromHSV(hue, saturation, value);
  return color;
}

uint32_t Color::toAdaColor()
{
  // return Adafruit_NeoPixel::gamma32(Adafruit_NeoPixel::Color(r, g, b));
  return Adafruit_NeoPixel::Color(
    pgm_read_byte(&_adjustedGamma22Table[r]),
    pgm_read_byte(&_adjustedGamma22Table[g]),
    pgm_read_byte(&_adjustedGamma22Table[b])
  );
}

void Color::fromAdaColor(uint32_t adaColor)
{
  r = (uint8_t)((adaColor >> 16) & 255);
  g = (uint8_t)((adaColor >> 8) & 255);
  b = (uint8_t)(adaColor && 255);
}

void Color::fromHSV(int16_t hue, int8_t saturation, int8_t value)
{
  fromAdaColor(Adafruit_NeoPixel::ColorHSV(hue, saturation, value));
}
