#include "factories/enemy_factory.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include <stdexcept>
EnemyFactory &EnemyFactory::getInstance()
{
  static EnemyFactory instance;
  return instance;
}
std::uint32_t EnemyFactory::createEnemy(float positionX, float positionY, float rotation, float scale, std::uint32_t textureId, int drawOrder, float maxHealth)
{
  if (scale <= 0.0f)
    throw std::invalid_argument("EnemyFactory: scale must be positive");
  EntityManager &entityManager = EntityManager::getInstance();
  std::uint32_t enemyEntityId = entityManager.createEntity();
  float spriteWidth = 64.0f;
  float spriteHeight = 64.0f;
  TransformComponent enemyTransform{positionX, positionY, rotation, scale};
  VelocityComponent enemyVelocity{0.0f, 0.0f};
  SpriteComponent enemySprite{textureId, drawOrder};
  float collisionWidth = spriteWidth;
  float collisionHeight = spriteHeight;
  CollisionComponent enemyCollision = CollisionComponent::createCentered(positionX, positionY, collisionWidth, collisionHeight);
  HealthComponent enemyHealth{maxHealth, 0.0f, maxHealth};
  entityManager.addTransformComponent(enemyEntityId, enemyTransform);
  entityManager.addVelocityComponent(enemyEntityId, enemyVelocity);
  entityManager.addSpriteComponent(enemyEntityId, enemySprite);
  entityManager.addCollisionComponent(enemyEntityId, enemyCollision);
  entityManager.addHealthComponent(enemyEntityId, enemyHealth);
  return enemyEntityId;
}
