#include "ecs/systems/aiming_system.h"
#include "ecs/entity_manager.h"
#include <SDL2/SDL.h>
#include <cmath>
AimingSystem &AimingSystem::getInstance()
{
  static AimingSystem instance;
  return instance;
}
AimingSystem::AimingSystem() {}
void AimingSystem::setPlayerEntityId(std::uint32_t id)
{
  playerEntityId = id;
}
void AimingSystem::update(float mouseX, float mouseY)
{
  EntityManager &entityManager = EntityManager::getInstance();
  TransformComponent *playerTransform = entityManager.getTransformComponent(playerEntityId);
  if (!playerTransform)
    return;
  float playerCenterX = playerTransform->positionX + 32.0f;
  float playerCenterY = playerTransform->positionY + 32.0f;
  float dx = mouseX - playerCenterX;
  float dy = mouseY - playerCenterY;
  aimAngle = std::atan2(dy, dx);
}
void AimingSystem::update()
{
  int mouseX = 0;
  int mouseY = 0;
  SDL_GetMouseState(&mouseX, &mouseY);
  update(static_cast<float>(mouseX), static_cast<float>(mouseY));
}
float AimingSystem::getAimAngle() const
{
  return aimAngle;
}
