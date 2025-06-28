#include "factories/enemy_factory.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include <stdexcept>
EnemyFactory &EnemyFactory::getInstance()
{
  static EnemyFactory instance;
  return instance;
}
std::uint32_t EnemyFactory::createEnemy(float positionX, float positionY, float rotation, float scale, std::uint32_t textureId, int drawOrder)
{
  if (scale <= 0.0f)
    throw std::invalid_argument("EnemyFactory: scale must be positive");
  EntityManager &entityManager = EntityManager::getInstance();
  std::uint32_t enemyEntityId = entityManager.createEntity();
  TransformComponent enemyTransform{positionX, positionY, rotation, scale};
  VelocityComponent enemyVelocity{0.0f, 0.0f};
  SpriteComponent enemySprite{textureId, drawOrder};
  entityManager.addTransformComponent(enemyEntityId, enemyTransform);
  entityManager.addVelocityComponent(enemyEntityId, enemyVelocity);
  entityManager.addSpriteComponent(enemyEntityId, enemySprite);
  return enemyEntityId;
}
