#pragma once
#include <cstdint>
class EnemyFactory
{
public:
  static EnemyFactory &getInstance();
  std::uint32_t createEnemy(float positionX, float positionY, float rotation, float scale, std::uint32_t textureId, int drawOrder, float maxHealth = 100.0f);

private:
  EnemyFactory() = default;
  EnemyFactory(const EnemyFactory &) = delete;
  EnemyFactory &operator=(const EnemyFactory &) = delete;
};
