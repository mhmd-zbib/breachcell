#pragma once
#include <cstdint>
class MovementSystem
{
public:
  static MovementSystem &getInstance();
  void update(float deltaTime);
  void setPlayerEntityId(std::uint32_t id);
  static constexpr float NORMAL_SPEED = 250.0f;
  static constexpr float SLOW_SPEED = 100.0f;

private:
  MovementSystem();
  std::uint32_t playerEntityId = 0;
};
