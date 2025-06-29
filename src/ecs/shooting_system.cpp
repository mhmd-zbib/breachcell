#include "ecs/systems/shooting_system.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include "input/input_handler.h"
#include "core/engine.h"
#include <SDL2/SDL.h>
#include <random>
#include "factories/projectile_factory.h"
#include <iostream> // Include iostream for logging

ShootingSystem &ShootingSystem::getInstance()
{
  static ShootingSystem instance;
  return instance;
}

ShootingSystem::ShootingSystem() {}

void ShootingSystem::update(std::uint32_t shooterEntityId)
{
  EntityManager &entityManager = EntityManager::getInstance();
  AimComponent *aim = entityManager.getAimComponent(shooterEntityId);
  if (!aim)
    return;
  InputHandler &inputHandler = InputHandler::getInstance();
  static bool wasPressed = false;
  static std::mt19937 gen(std::random_device{}());
  static Uint32 lastShotTime = 0;
  static constexpr Uint32 fireDelay = 100;
  bool isPressed = (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT));
  aim->isShooting = isPressed;
  Uint32 now = SDL_GetTicks();
  if (isPressed && (now - lastShotTime >= fireDelay))
  {
    TransformComponent *playerTransform = entityManager.getTransformComponent(shooterEntityId);
    CollisionComponent *playerCollision = entityManager.getCollisionComponent(shooterEntityId);
    if (!playerTransform)
      return;
    float aimAngle = aim->aimAngle;
    float preShotHalfCone = aim->aimConeHalfAngle;
    std::uniform_real_distribution<float> dist(aimAngle - preShotHalfCone, aimAngle + preShotHalfCone);
    float spreadAngle = dist(gen);
    float speed = ShootingSystem::PROJECTILE_SPEED;
    float spawnX = playerTransform->positionX;
    float spawnY = playerTransform->positionY;
    float width = playerCollision ? playerCollision->boxWidth : 64.0f;
    float height = playerCollision ? playerCollision->boxHeight : 64.0f;
    if (playerCollision)
    {
      spawnX += playerCollision->offsetX;
      spawnY += playerCollision->offsetY;
    }
    spawnX += 0.0f;
    spawnY += 0.0f;
    float centerX = playerTransform->positionX + (playerCollision ? playerCollision->offsetX : 0.0f);
    float centerY = playerTransform->positionY + (playerCollision ? playerCollision->offsetY : 0.0f);
    float sideOffset = (playerCollision ? 0.5f * playerCollision->boxWidth : 32.0f);
    float projectileRadius = 4.0f;
    float sideAngle = spreadAngle + static_cast<float>(M_PI_2);
    float sideX = centerX + std::cos(sideAngle) * sideOffset;
    float sideY = centerY + std::sin(sideAngle) * sideOffset;
    spawnX = sideX + std::cos(spreadAngle) * projectileRadius;
    spawnY = sideY + std::sin(spreadAngle) * projectileRadius;
    float velocityX = std::cos(spreadAngle) * speed;
    float velocityY = std::sin(spreadAngle) * speed;
    float lifetime = 1.5f;
    std::string textureId = "projectile";
    ProjectileFactory::getInstance().createProjectile(
        spawnX, spawnY, velocityX, velocityY, width, height, lifetime, textureId, shooterEntityId);
    lastShotTime = now;
    std::cout << "ShootingSystem: centerX=" << centerX << " centerY=" << centerY << std::endl;
    std::cout << "ShootingSystem: calculated spawnX=" << spawnX << " spawnY=" << spawnY << " spreadAngle=" << spreadAngle << std::endl;
  }
  wasPressed = isPressed;
}
