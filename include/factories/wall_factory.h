#pragma once
#include <cstdint>
#include "ecs/entity_manager.h"

class WallFactory : public IEntityFactory
{
public:
  static WallFactory &getInstance();
  std::uint32_t create() override;
  std::uint32_t createWall(float positionX, float positionY, float width, float height, int drawOrder);

private:
  WallFactory() = default;
  WallFactory(const WallFactory &) = delete;
  WallFactory &operator=(const WallFactory &) = delete;
};
