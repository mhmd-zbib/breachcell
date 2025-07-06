#pragma once
#include <cstdint>
#include "ecs/entity_manager.h"
class PlayerFactory : public IEntityFactory
{
public:
  static PlayerFactory& getInstance();
  std::uint32_t create() override;
  std::uint32_t createPlayer(float positionX, float positionY, float rotation, float scale,
                             std::uint32_t textureId, int drawOrder);

private:
  PlayerFactory() = default;
  PlayerFactory(const PlayerFactory&) = delete;
  PlayerFactory& operator=(const PlayerFactory&) = delete;
};
