#include "factories/player_factory.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include <stdexcept>
#include <iostream>

PlayerFactory& PlayerFactory::getInstance()
{
  static PlayerFactory instance;
  return instance;
}

std::uint32_t PlayerFactory::createPlayer(float positionX, float positionY, float rotation,
    float scale, std::uint32_t textureId, int drawOrder)
{
  if (scale <= 0.0f)
  {
    throw std::invalid_argument("PlayerFactory: scale must be positive");
  }

  EntityManager& entityManager = EntityManager::getInstance();
  std::uint32_t playerEntityId = entityManager.createEntity();
  constexpr float spriteWidth = 64.0f;
  constexpr float spriteHeight = 64.0f;
  TransformComponent playerTransform{positionX, positionY, rotation, scale};
  VelocityComponent playerVelocity{0.0f, 0.0f};
  SpriteComponent playerSprite{textureId, drawOrder};
  InputComponent playerInput{false, false, false, false};
  AimComponent playerAim{};
  playerAim.aimAngle = 0.0f;
  playerAim.aimConeHalfAngle = 0.0f;
  playerAim.currentConeDegrees = 6.0f;
  playerAim.targetConeDegrees = 6.0f;
  playerAim.isShooting = false;
  playerAim.standingStillTime = 0.0f;
  playerAim.lastVelocityMagnitude = 0.0f;
  playerAim.lastUpdateTime = 0.0f;
  entityManager.addTransformComponent(playerEntityId, playerTransform);
  entityManager.addVelocityComponent(playerEntityId, playerVelocity);
  entityManager.addSpriteComponent(playerEntityId, playerSprite);
  entityManager.addInputComponent(playerEntityId, playerInput);
  entityManager.addComponent(playerEntityId, playerAim);
  std::cout << "PlayerFactory: Created player entity " << playerEntityId << " at (" << positionX <<
            ", " << positionY << ")" << std::endl;
  return playerEntityId;
}

std::uint32_t PlayerFactory::create()
{
  return createPlayer(400.0f, 300.0f, 0.0f, 1.0f, 1, 0);
}
