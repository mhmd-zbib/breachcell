#include "ecs/systems/shooting_system.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include "input/input_handler.h"
#include "core/engine.h"
#include <SDL2/SDL.h>
#include <random>
#include "factories/projectile_factory.h"
#include "ecs/systems/aiming_system.h"

ShootingSystem &ShootingSystem::getInstance()
{
  static ShootingSystem instance;
  return instance;
}

ShootingSystem::ShootingSystem() {}

void ShootingSystem::update(std::uint32_t playerEntityId)
{
  InputHandler &inputHandler = InputHandler::getInstance();
  static bool wasPressed = false;
  static std::mt19937 gen(std::random_device{}());
  static Uint32 lastShotTime = 0;
  static constexpr Uint32 fireDelay = 100;
  bool isPressed = (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT));
  EntityManager &entityManager = EntityManager::getInstance();
  AimComponent *aim = entityManager.getAimComponent(playerEntityId);
  if (aim)
    aim->isShooting = isPressed;
  Uint32 now = SDL_GetTicks();
  if (isPressed && (now - lastShotTime >= fireDelay))
  {
    TransformComponent *playerTransform = entityManager.getTransformComponent(playerEntityId);
    CollisionComponent *playerCollision = entityManager.getCollisionComponent(playerEntityId);
    if (!playerTransform || !aim)
      return;
    float aimAngle = aim->aimAngle;
    float preShotHalfCone = aim->aimConeHalfAngle;
    std::uniform_real_distribution<float> dist(aimAngle - preShotHalfCone, aimAngle + preShotHalfCone);
    float spreadAngle = dist(gen);
    float speed = ShootingSystem::PROJECTILE_SPEED;
    float spawnX = playerTransform->positionX;
    float spawnY = playerTransform->positionY;
    float offsetDistance = 0.0f;
    float projectileRadius = 4.0f;
    if (playerCollision)
    {
      spawnX += playerCollision->offsetX;
      spawnY += playerCollision->offsetY;
      float playerRadius = 0.5f * std::max(playerCollision->boxWidth, playerCollision->boxHeight);
      offsetDistance = playerRadius + projectileRadius + 1.0f;
      spawnX += std::cos(spreadAngle) * offsetDistance;
      spawnY += std::sin(spreadAngle) * offsetDistance;
    }
    float velocityX = std::cos(spreadAngle) * speed;
    float velocityY = std::sin(spreadAngle) * speed;
    float width = 8.0f;
    float height = 8.0f;
    float lifetime = 1.5f;
    std::string textureId = "projectile";
    ProjectileFactory::getInstance().createProjectile(
        spawnX, spawnY, velocityX, velocityY, width, height, lifetime, textureId, playerEntityId);
    lastShotTime = now;
  }
  wasPressed = isPressed;
}
