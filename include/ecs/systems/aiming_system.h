#pragma once
#include <cstdint>
class AimingSystem
{
public:
  static AimingSystem &getInstance();
  void setPlayerEntityId(std::uint32_t id);
  void update(float mouseX, float mouseY);
  void update();
  float getAimAngle() const;

private:
  AimingSystem();
  std::uint32_t playerEntityId = 0;
  float aimAngle = 0.0f;
};
