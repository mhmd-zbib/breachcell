#pragma once
#include <cstdint>
class MovementSystem
{
public:
  static MovementSystem &getInstance();
  void update(float deltaTime);
  void setPlayerEntityId(std::uint32_t id); // Set the player entity ID

private:
  MovementSystem();
  std::uint32_t playerEntityId = 0; // Store the player entity ID
};
