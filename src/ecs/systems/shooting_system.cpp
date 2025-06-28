#include "ecs/systems/shooting_system.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include "input/input_handler.h"
#include "core/engine.h"
#include <SDL2/SDL.h>
#include <random>

ShootingSystem &ShootingSystem::getInstance()
{
  static ShootingSystem instance;
  return instance;
}

ShootingSystem::ShootingSystem() {}

void ShootingSystem::setPlayerEntityId(std::uint32_t id)
{
  playerEntityId = id;
}

void ShootingSystem::update()
{
  InputHandler &inputHandler = InputHandler::getInstance();
  static bool wasPressed = false;
  static std::mt19937 gen(std::random_device{}());
  static Uint32 lastShotTime = 0;
  static constexpr Uint32 fireDelay = 200;
  bool isPressed = (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT));
  Uint32 now = SDL_GetTicks();
  if (isPressed && (now - lastShotTime >= fireDelay))
  {
    EntityManager &entityManager = EntityManager::getInstance();
    TransformComponent *playerTransform = entityManager.getTransformComponent(playerEntityId);
    if (!playerTransform)
      return;
    float aimAngle = AimingSystem::getInstance().getAimAngle();
    float halfCone = 17.5f * 3.14159265f / 180.0f;
    std::uniform_real_distribution<float> dist(aimAngle - halfCone, aimAngle + halfCone);
    float spreadAngle = dist(gen);
    float speed = 400.0f;
    float spawnX = playerTransform->positionX + 32.0f;
    float spawnY = playerTransform->positionY + 32.0f;
    std::uint32_t projectileId = entityManager.createEntity();
    TransformComponent projectileTransform{spawnX, spawnY, spreadAngle, 1.0f};
    VelocityComponent projectileVelocity{std::cos(spreadAngle) * speed, std::sin(spreadAngle) * speed};
    ProjectileComponent projectileData{1.5f, 10.0f};
    entityManager.addTransformComponent(projectileId, projectileTransform);
    entityManager.addVelocityComponent(projectileId, projectileVelocity);
    entityManager.addProjectileComponent(projectileId, projectileData);
    lastShotTime = now;
  }
  wasPressed = isPressed;
}
