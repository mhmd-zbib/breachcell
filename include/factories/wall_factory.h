#pragma once
#include <cstdint>

class WallFactory
{
public:
  static WallFactory &getInstance();
  std::uint32_t createWall(float positionX, float positionY, float width, float height, int drawOrder);

private:
  WallFactory() = default;
  WallFactory(const WallFactory &) = delete;
  WallFactory &operator=(const WallFactory &) = delete;
};
