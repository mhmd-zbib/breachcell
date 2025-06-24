#pragma once
#include <cstdint>
class MovementSystem
{
public:
  static MovementSystem &getInstance();
  void update(float deltaTime);

private:
  MovementSystem();
};
