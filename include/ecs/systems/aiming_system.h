#pragma once
#include <cstdint>
#include "core/math_utils.h"

class AimingSystem
{
public:
  static AimingSystem &getInstance();
  void setPlayerEntityId(std::uint32_t id);
  void update(float mouseX, float mouseY);
  void update();
  float getAimAngle() const;
  float getAimConeHalfAngle() const;

private:
  AimingSystem();
  std::uint32_t playerEntityId = 0;
  float aimAngle = 0.0f;
  float aimConeHalfAngle = 0.0f;

  static constexpr float STANDING_CONE_DEGREES = 3.0f;
  static constexpr float WALKING_CONE_DEGREES = 35.0f;
  // All aiming constants already present in header.
};
