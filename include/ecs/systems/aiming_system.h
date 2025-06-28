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
  float getShootConeHalfAngle() const;
  void setShooting(bool shooting);     // No longer affects cone logic
  void triggerPostShotConeExpansion(); // Call after a shot to expand cone

private:
  AimingSystem();
  std::uint32_t playerEntityId = 0;
  float aimAngle = 0.0f;
  float aimConeHalfAngle = 0.0f;
  bool isShooting = false;

  float standingStillTime = 0.0f;
  float lastVelocityMag = 0.0f;
  float lastUpdateTime = 0.0f;
  float currentConeDegrees = STANDING_CONE_DEGREES;
  float targetConeDegrees = STANDING_CONE_DEGREES;
  float coneTransitionSpeed = 120.0f;

  static constexpr float STANDING_FOCUSED_CONE_DEGREES = 0.1f; // After standing still for 2 seconds.
  static constexpr float STANDING_CONE_DEGREES = 4.0f;         // Default when standing.
  static constexpr float STANDING_SHOOT_CONE_DEGREES = 8.0f;   // Standing but shooting.
  static constexpr float SLOW_WALK_CONE_DEGREES = 7.0f;        // Slow walking.
  static constexpr float SLOW_WALK_SHOOT_CONE_DEGREES = 15.0f; // Shooting while slow walking.
  static constexpr float WALKING_CONE_DEGREES = 20.0f;         // Normal walking.
  static constexpr float WALKING_SHOOT_CONE_DEGREES = 35.0f;   // Shooting while walking.
};
