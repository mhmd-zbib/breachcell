#pragma once
#include <cstdint>

class ShootingSystem
{
public:
  static ShootingSystem &getInstance();
  void update(std::uint32_t playerEntityId);

private:
  ShootingSystem();
  ShootingSystem(const ShootingSystem &) = delete;
  ShootingSystem &operator=(const ShootingSystem &) = delete;
  static constexpr float PROJECTILE_SPEED = 400.0f;
};
