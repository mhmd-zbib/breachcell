#pragma once
#include <cstdint>
#include "ecs/systems/aiming_system.h"

class ShootingSystem
{
public:
  static ShootingSystem &getInstance();
  void update();
  void setPlayerEntityId(std::uint32_t id);

private:
  ShootingSystem();
  std::uint32_t playerEntityId = 0;
};
