#ifndef TEST_ROTATION_UTILS_H
#define TEST_ROTATION_UTILS_H
#include <cassert>
#include <cmath>
namespace TestRotationUtils
{
float calculateAngleToTarget(float sourceX, float sourceY, float targetX, float targetY)
{
    float dx = targetX - sourceX;
    float dy = targetY - sourceY;
    if (dx == 0.0f && dy == 0.0f)
        return 0.0f;
    return std::atan2(dy, dx) * 180.0f / static_cast<float>(M_PI);
}
void runTests()
{
    assert(std::abs(calculateAngleToTarget(0, 0, 1, 0) - 0.0f) < 0.01f);
    assert(std::abs(calculateAngleToTarget(0, 0, 0, 1) - 90.0f) < 0.01f);
    assert(std::abs(calculateAngleToTarget(0, 0, -1, 0) - 180.0f) < 0.01f);
    assert(std::abs(calculateAngleToTarget(0, 0, 0, -1) + 90.0f) < 0.01f);
    assert(std::abs(calculateAngleToTarget(1, 1, 1, 1) - 0.0f) < 0.01f);
}
} // namespace TestRotationUtils
#endif
