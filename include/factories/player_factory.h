#pragma once
#include <cstdint>
class PlayerFactory
{
public:
  static PlayerFactory &getInstance();
  std::uint32_t createPlayer(float positionX, float positionY, float rotation, float scale, std::uint32_t textureId, int drawOrder);

private:
  PlayerFactory() = default;
  PlayerFactory(const PlayerFactory &) = delete;
  PlayerFactory &operator=(const PlayerFactory &) = delete;
};
