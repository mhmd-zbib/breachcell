#pragma once
#include <cmath>
namespace MathUtils
{
  static constexpr float PI = 3.14159265f;
  static constexpr float DEG_TO_RAD = PI / 180.0f;
  static constexpr float RAD_TO_DEG = 180.0f / PI;
  inline float toRadians(float degrees) { return degrees * DEG_TO_RAD; }
  inline float toDegrees(float radians) { return radians * RAD_TO_DEG; }
  inline float vectorMagnitude(float x, float y) { return std::sqrt(x * x + y * y); }
}

// Math constants already present in header.
