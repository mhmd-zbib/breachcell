#include "ecs/systems/shooting_system.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include "factories/projectile_builder.h"
#include "factories/projectile_factory.h"
#include <SDL2/SDL.h>
#include <random>
#include <iostream>

ShootingSystem& ShootingSystem::getInstance()
{
  static ShootingSystem instance;
  return instance;
}

ShootingSystem::ShootingSystem() {}

void ShootingSystem::update(std::uint32_t shooterEntityId)
{
  EntityManager& entityManager = EntityManager::getInstance();
  AimComponent* aimComponent = entityManager.getAimComponent(shooterEntityId);

  if (!aimComponent)
  {
    return;
  }

  static bool mouseButtonPreviouslyPressed = false;
  static Uint32 lastProjectileShotTime = 0;
  static constexpr Uint32 PROJECTILE_FIRE_DELAY = 100;
  bool mouseButtonCurrentlyPressed = (SDL_GetMouseState(nullptr,
                                      nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT));
  aimComponent->isShooting = mouseButtonCurrentlyPressed;
  Uint32 currentTime = SDL_GetTicks();

  if (mouseButtonCurrentlyPressed && !mouseButtonPreviouslyPressed
      && (currentTime - lastProjectileShotTime >= PROJECTILE_FIRE_DELAY))
  {
    TransformComponent* shooterTransformComponent = entityManager.getTransformComponent(
          shooterEntityId);

    if (!shooterTransformComponent)
    {
      return;
    }

    float shooterAimAngle = aimComponent->aimAngle;
    float shooterProjectileSpeed = ShootingSystem::PROJECTILE_SPEED;
    float shooterPositionX = shooterTransformComponent->positionX;
    float shooterPositionY = shooterTransformComponent->positionY;
    float projectileRadius = 4.0f;
    float projectileSpawnMargin = 16.0f;
    float projectileSpawnOffset = 0.5f * projectileRadius + projectileSpawnMargin;
    float projectileSpawnX = shooterPositionX + std::cos(shooterAimAngle) * projectileSpawnOffset;
    float projectileSpawnY = shooterPositionY + std::sin(shooterAimAngle) * projectileSpawnOffset;
    float projectileWidth = 4.0f;
    float projectileHeight = 4.0f;
    float projectileVelocityX = std::cos(shooterAimAngle) * shooterProjectileSpeed;
    float projectileVelocityY = std::sin(shooterAimAngle) * shooterProjectileSpeed;
    float projectileLifetime = 1.5f;
    std::string projectileTextureId = "1";
    ProjectileFactory::getInstance().createProjectile(
      projectileSpawnX,
      projectileSpawnY,
      projectileVelocityX,
      projectileVelocityY,
      projectileWidth,
      projectileHeight,
      projectileLifetime,
      projectileTextureId,
      shooterEntityId);
    lastProjectileShotTime = currentTime;
  }

  mouseButtonPreviouslyPressed = mouseButtonCurrentlyPressed;
}
