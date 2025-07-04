#pragma once
#include <cstdint>

class AimingSystem
{
public:
  static AimingSystem &getInstance();
  void update(std::uint32_t playerEntityId, float mousePositionX, float mousePositionY);
  void update(std::uint32_t playerEntityId);
  float getAimAngle() const;
  float getAimConeHalfAngle() const;
  float getShootConeHalfAngle(std::uint32_t playerEntityId) const;
  void setShooting(bool shootingState);
  void triggerPostShotConeExpansion(std::uint32_t playerEntityId);

private:
  AimingSystem();
  AimingSystem(const AimingSystem &) = delete;
  AimingSystem &operator=(const AimingSystem &) = delete;
  float aimAngle = 0.0f;
  float aimConeHalfAngle = 0.0f;
  bool isShooting = false;
  float standingStillTime = 0.0f;
  float lastVelocityMagnitude = 0.0f;
  float lastUpdateTime = 0.0f;
  float currentConeDegrees = 0.0f;
  float targetConeDegrees = 0.0f;
  static constexpr float STANDING_CONE_DEGREES = 6.0f;
  static constexpr float STANDING_FOCUSED_CONE_DEGREES = 2.0f;
  static constexpr float SLOW_WALK_CONE_DEGREES = 10.0f;
  static constexpr float WALKING_CONE_DEGREES = 18.0f;
  static constexpr float STANDING_SHOOT_CONE_DEGREES = 8.0f;
  static constexpr float SLOW_WALK_SHOOT_CONE_DEGREES = 14.0f;
  static constexpr float WALKING_SHOOT_CONE_DEGREES = 24.0f;
  static constexpr float coneTransitionSpeed = 40.0f;
};
