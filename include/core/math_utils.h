#pragma once
#include <cmath>
namespace MathUtils
{
static constexpr float PI = 3.14159265f;
static constexpr float DEG_TO_RAD = PI / 180.0f;
static constexpr float RAD_TO_DEG = 180.0f / PI;
inline float toRadians(float degrees)
{
  return degrees * DEG_TO_RAD;
}
inline float toDegrees(float radians)
{
  return radians * RAD_TO_DEG;
}
inline float vectorMagnitude(float x, float y)
{
  return std::sqrt(x * x + y * y);
}
// Returns true if two AABBs overlap
inline bool aabbOverlap(float minAx, float maxAx, float minAy, float maxAy,
                        float minBx, float maxBx, float minBy, float maxBy)
{
  return (minAx < maxBx && maxAx > minBx && minAy < maxBy && maxAy > minBy);
}
// Sweep test: returns true if a box moving from (start) to (end) would overlap any static box
// (Assumes linear movement, no rotation)
// Returns true if any overlap is found along the path
template <typename OverlapFn>
bool sweepTest(float startX, float startY, float endX, float endY, float boxW, float boxH,
               OverlapFn overlapFn, float step = 2.0f)
{
  float dx = endX - startX;
  float dy = endY - startY;
  float dist = vectorMagnitude(dx, dy);
  int steps = std::max(1, static_cast<int>(dist / step));

  for (int i = 0; i <= steps; ++i)
  {
    float t = (steps == 0) ? 0.0f : (float)i / steps;
    float cx = startX + dx * t;
    float cy = startY + dy * t;
    float minX = cx - boxW * 0.5f;
    float maxX = cx + boxW * 0.5f;
    float minY = cy - boxH * 0.5f;
    float maxY = cy + boxH * 0.5f;

    if (overlapFn(minX, maxX, minY, maxY))
    {
      return true;
    }
  }

  return false;
}
}

// Math constants already present in header.
