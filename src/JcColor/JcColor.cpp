#include "Adafruit_NeoPixel.h"
#include "JcColor.h"

Color Color::operator+(const Color& other) const
{
  uint32_t resultR = r + other.r;
  uint32_t resultG = g + other.g;
  uint32_t resultB = b + other.b;
  
  resultR = resultR > 65535 ? 65535 : resultR;
  resultG = resultG > 65535 ? 65535 : resultG;
  resultB = resultB > 65535 ? 65535 : resultB;

  return Color{
    static_cast<uint16_t>(resultR), 
    static_cast<uint16_t>(resultG),
    static_cast<uint16_t>(resultB)
  };
}

Color Color::operator*(float scalar) const
{
  float resultR = r * scalar;
  float resultG = g * scalar;
  float resultB = b * scalar;

  resultR = resultR > 65535 ? 65535 : resultR;
  resultG = resultG > 65535 ? 65535 : resultG;
  resultB = resultB > 65535 ? 65535 : resultB;
  resultR = resultR < 0 ? 0 : resultR;
  resultG = resultG < 0 ? 0 : resultG;
  resultB = resultB < 0 ? 0 : resultB;

  return Color{
    static_cast<uint16_t>(resultR), 
    static_cast<uint16_t>(resultG),
    static_cast<uint16_t>(resultB)
  };
}

Color Color::FromRGB(uint8_t r, uint8_t g, uint8_t b)
{
  return Color{
    static_cast<uint16_t>(r*256), 
    static_cast<uint16_t>(g*256), 
    static_cast<uint16_t>(b*256)
  };
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

Color Color::lerp(const Color& a, const Color& b, float t)
{
  t = t < 0 ? 0 : t;
  t = t > 1 ? 1 : t;

  return Color(a*(1-t) + b*(t));
}

uint32_t Color::toAdaColor() const
{
  // return Adafruit_NeoPixel::gamma32(Adafruit_NeoPixel::Color(r, g, b));
  return Adafruit_NeoPixel::Color(
    pgm_read_byte(&_adjustedGamma22Table[getR()]),
    pgm_read_byte(&_adjustedGamma22Table[getG()]),
    pgm_read_byte(&_adjustedGamma22Table[getB()])
  );
}

void Color::fromAdaColor(uint32_t adaColor)
{
  r = (uint8_t)((adaColor >> 16) & 255) * 255;
  g = (uint8_t)((adaColor >> 8) & 255) * 255;
  b = (uint8_t)(adaColor & 255) * 255;
}

void Color::fromHSV(int16_t hue, int8_t saturation, int8_t value)
{
  fromAdaColor(Adafruit_NeoPixel::ColorHSV(hue, saturation, value));
}

void Color::fromRGB24(int8_t r, int8_t g, int8_t b)
{

}

uint8_t Color::getR() const
{
  return r/255;
}

uint8_t Color::getG() const
{
  return g/255;
}

uint8_t Color::getB() const
{
  return b/255;
}
