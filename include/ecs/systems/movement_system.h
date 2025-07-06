#pragma once
#include <cstdint>
class MovementSystem
{
public:
  static MovementSystem& getInstance();
  void update(float deltaTime, std::uint32_t playerEntityId);
  static constexpr float NORMAL_SPEED = 300.0f;
  static constexpr float SLOW_SPEED = 150.0f;

private:
  MovementSystem();
};
