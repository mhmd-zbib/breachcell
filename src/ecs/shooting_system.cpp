#include "ecs/systems/shooting_system.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include "input/input_handler.h"
#include "core/engine.h"
#include <SDL2/SDL.h>
#include <random>
#include "factories/projectile_factory.h"
#include <iostream>
#include "core/math_utils.h"

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
  static bool wasPressed = false;
  static std::mt19937 gen(std::random_device{}());
  static Uint32 lastShotTime = 0;
  static constexpr Uint32 fireDelay = 100;
  bool isPressed = (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT));
  aim->isShooting = isPressed;
  Uint32 now = SDL_GetTicks();
  if (isPressed && !wasPressed && (now - lastShotTime >= fireDelay)) // Only fire on click, not hold
  {
    TransformComponent *playerTransform = entityManager.getTransformComponent(shooterEntityId);
    if (!playerTransform)
      return;
    float aimAngle = aim->aimAngle;
    float coneHalf = aim->aimConeHalfAngle;
    std::uniform_real_distribution<float> dist(aimAngle - coneHalf, aimAngle + coneHalf);
    float spreadAngle = dist(gen);
    float speed = ShootingSystem::PROJECTILE_SPEED;
    float centerX = playerTransform->positionX;
    float centerY = playerTransform->positionY;
    float projectileRadius = 4.0f;
    float margin = 16.0f;
    float safeOffset = 0.5f * projectileRadius + margin;
    float spawnX = centerX + std::cos(aim->aimAngle) * safeOffset;
    float spawnY = centerY + std::sin(aim->aimAngle) * safeOffset;
    float width = 8.0f;
    float height = 8.0f;
    float velocityX = std::cos(aim->aimAngle) * speed;
    float velocityY = std::sin(aim->aimAngle) * speed;
    float lifetime = 1.5f;
    std::string textureId = "projectile";
    ProjectileFactory::getInstance().createProjectile(
        spawnX, spawnY, velocityX, velocityY, width, height, lifetime, textureId, shooterEntityId);
    std::cout << "Projectile spawned: entityId=" << shooterEntityId << " spawnX=" << spawnX << " spawnY=" << spawnY << " angle=" << aim->aimAngle << std::endl;
    lastShotTime = now;
  }
  wasPressed = isPressed;
}
