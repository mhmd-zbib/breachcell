#pragma once
#include <cstdint>
class CollisionSystem
{
public:
  static CollisionSystem &getInstance();
  void update();
  void renderDebug();

private:
  CollisionSystem() = default;
  CollisionSystem(const CollisionSystem &) = delete;
  CollisionSystem &operator=(const CollisionSystem &) = delete;
};
