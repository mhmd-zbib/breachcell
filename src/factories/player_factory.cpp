#include "factories/player_factory.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include <stdexcept>

PlayerFactory &PlayerFactory::getInstance()
{
  static PlayerFactory instance;
  return instance;
}

std::uint32_t PlayerFactory::createPlayer(float positionX, float positionY, float rotation, float scale, std::uint32_t textureId, int drawOrder)
{
  if (scale <= 0.0f)
    throw std::invalid_argument("PlayerFactory: scale must be positive");
  EntityManager &entityManager = EntityManager::getInstance();
  std::uint32_t playerEntityId = entityManager.createEntity();
  float spriteWidth = 64.0f;
  float spriteHeight = 64.0f;
  TransformComponent playerTransform{positionX, positionY, rotation, scale};
  VelocityComponent playerVelocity{0.0f, 0.0f};
  SpriteComponent playerSprite{textureId, drawOrder};
  InputComponent playerInput{false, false, false, false};
  float collisionWidth = spriteWidth;
  float collisionHeight = spriteHeight;
  float collisionOffsetX = 0.0f;
  float collisionOffsetY = 0.0f;
  CollisionComponent playerCollision = CollisionComponent::createCentered(collisionOffsetX, collisionOffsetY, collisionWidth, collisionHeight);
  entityManager.addTransformComponent(playerEntityId, playerTransform);
  entityManager.addVelocityComponent(playerEntityId, playerVelocity);
  entityManager.addSpriteComponent(playerEntityId, playerSprite);
  entityManager.addInputComponent(playerEntityId, playerInput);
  entityManager.addCollisionComponent(playerEntityId, playerCollision);
  return playerEntityId;
}

std::uint32_t PlayerFactory::create()
{
  return createPlayer(400.0f, 300.0f, 0.0f, 1.0f, 1, 0);
}
