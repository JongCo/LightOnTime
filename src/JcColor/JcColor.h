#pragma once
#include "Arduino.h"

struct Color{
  uint16_t r;
  uint16_t g;
  uint16_t b;

  Color operator+(const Color& other) const;
  Color operator*(float scalar) const;

  uint32_t toAdaColor() const;
  void fromAdaColor(uint32_t adaColor);
  void fromHSV(int16_t hue, int8_t saturation, int8_t value);
  void fromRGB24(int8_t r8, int8_t g8, int8_t b8);

  uint8_t getR() const;
  uint8_t getG() const;
  uint8_t getB() const;

  static Color FromRGB(uint8_t r, uint8_t g, uint8_t b);
  static Color FromAdaColor(int32_t adaColor);
  static Color FromHSV(uint16_t hue, int8_t saturation, int8_t value);

  static Color lerp(const Color& a, const Color& b, float t);

};

static const uint8_t PROGMEM _adjustedGamma22Table[256] = {
  0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3,
  3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5,
  6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10,
  10, 11, 11, 11, 12, 12, 12, 13, 13, 14, 14, 15, 15, 15, 16, 16,
  17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24,
  25, 26, 26, 27, 27, 28, 28, 29, 30, 30, 31, 32, 32, 33, 34, 35,
  35, 36, 37, 38, 39, 39, 40, 41, 42, 43, 43, 44, 45, 46, 47, 48,
  49, 50, 51, 52, 53, 53, 54, 55, 56, 57, 58, 59, 60, 62, 63, 64,
  65, 66, 67, 68, 69, 70, 71, 73, 74, 75, 76, 77, 78, 80, 81, 82,
  83, 85, 86, 87, 88, 90, 91, 92, 94, 95, 96, 98, 99, 100, 102, 103,
  105, 106, 108, 109, 111, 112, 114, 115, 117, 118, 120, 121, 123, 124, 126, 127,
  129, 131, 132, 134, 136, 137, 139, 141, 142, 144, 146, 148, 149, 151, 153, 155,
  156, 158, 160, 162, 164, 166, 167, 169, 171, 173, 175, 177, 179, 181, 183, 185,
  187, 189, 191, 193, 195, 197, 199, 201, 203, 205, 207, 210, 212, 214, 216, 218,
  220, 223, 225, 227, 229, 232, 234, 236, 239, 241, 243, 246, 248, 250, 253, 255
};