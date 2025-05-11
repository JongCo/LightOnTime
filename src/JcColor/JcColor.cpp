#include "Adafruit_NeoPixel.h"
#include "JcColor.h"

Color Color::operator+(const Color& other) const
{
  uint16_t resultR = r + other.r;
  uint16_t resultG = r + other.r;
  uint16_t resultB = r + other.r;
  
  resultR = resultR > 255 ? 255 : resultR;
  resultG = resultG > 255 ? 255 : resultG;
  resultB = resultB > 255 ? 255 : resultB;

  return Color{
    static_cast<uint8_t>(resultR), 
    static_cast<uint8_t>(resultG),
    static_cast<uint8_t>(resultB)
  };
}

Color Color::operator*(float scalar) const
{
  float resultR = r * scalar;
  float resultG = g * scalar;
  float resultB = b * scalar;

  resultR = resultR > 255 ? 255 : resultR;
  resultG = resultG > 255 ? 255 : resultG;
  resultB = resultB > 255 ? 255 : resultB;
  resultR = resultR < 0 ? 0 : resultR;
  resultG = resultG < 0 ? 0 : resultG;
  resultB = resultB < 0 ? 0 : resultB;

  return Color{
    static_cast<uint8_t>(resultR), 
    static_cast<uint8_t>(resultG),
    static_cast<uint8_t>(resultB)
  };
}

Color Color::FromRGB(uint8_t r, uint8_t g, uint8_t b)
{
  Color color;
  color.r = r;
  color.g = g;
  color.b = b;
  return color;
}

Color Color::FromAdaColor(int32_t adaColor)
{
  Color color;
  color.fromAdaColor(adaColor);
  return color;
}

Color Color::FromHSV(uint16_t hue, int8_t saturation, int8_t value)
{
  Color color;
  color.fromHSV(hue, saturation, value);
  return color;
}

Color Color::Lerp(const Color& a, const Color& b, float t)
{
  t = t < 0 ? 0 : t;
  t = t > 1 ? 1 : t;

  return Color(a*(1-t) + b*(t));
}

uint32_t Color::toAdaColor() const
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
  b = (uint8_t)(adaColor & 255);
}

void Color::fromHSV(int16_t hue, int8_t saturation, int8_t value)
{
  fromAdaColor(Adafruit_NeoPixel::ColorHSV(hue, saturation, value));
}
