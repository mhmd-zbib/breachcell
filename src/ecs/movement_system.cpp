#include "ecs/systems/movement_system.h"
#include "ecs/entity_manager.h"
#include "input/input_handler.h"
#include <cmath>

MovementSystem &MovementSystem::getInstance()
{
  static MovementSystem instance;
  return instance;
}

MovementSystem::MovementSystem() {}

void MovementSystem::update(float deltaTime, std::uint32_t playerEntityId)
{
  std::printf("MovementSystem::update playerEntityId: %u\n", playerEntityId);
  EntityManager &entityManager = EntityManager::getInstance();
  InputHandler &inputHandler = InputHandler::getInstance();
  auto velocity = entityManager.getVelocityComponent(playerEntityId);
  auto transform = entityManager.getTransformComponent(playerEntityId);
  if (velocity && transform)
  {
    velocity->velocityX = 0.0f;
    velocity->velocityY = 0.0f;
    float speed = inputHandler.isKeyPressed(SDLK_LSHIFT) || inputHandler.isKeyPressed(SDLK_RSHIFT) ? SLOW_SPEED : NORMAL_SPEED;
    bool wKey = inputHandler.isKeyPressed(SDLK_w);
    bool wScan = inputHandler.isKeyPressed(SDL_SCANCODE_W);
    bool sKey = inputHandler.isKeyPressed(SDLK_s);
    bool sScan = inputHandler.isKeyPressed(SDL_SCANCODE_S);
    bool aKey = inputHandler.isKeyPressed(SDLK_a);
    bool aScan = inputHandler.isKeyPressed(SDL_SCANCODE_A);
    bool dKey = inputHandler.isKeyPressed(SDLK_d);
    bool dScan = inputHandler.isKeyPressed(SDL_SCANCODE_D);
    std::printf("MovementSystem: W=%d WS=%d S=%d SS=%d A=%d AS=%d D=%d DS=%d\n", wKey, wScan, sKey, sScan, aKey, aScan, dKey, dScan);
    if (wKey || wScan)
      velocity->velocityY = -1.0f;
    if (sKey || sScan)
      velocity->velocityY = 1.0f;
    if (aKey || aScan)
      velocity->velocityX = -1.0f;
    if (dKey || dScan)
      velocity->velocityX = 1.0f;
    std::printf("MovementSystem::update velocity: %.2f, %.2f\n", velocity->velocityX, velocity->velocityY);
    float magnitude = std::sqrt(velocity->velocityX * velocity->velocityX + velocity->velocityY * velocity->velocityY);
    if (magnitude > 0.0f)
    {
      velocity->velocityX = (velocity->velocityX / magnitude) * NORMAL_SPEED;
      velocity->velocityY = (velocity->velocityY / magnitude) * NORMAL_SPEED;
    }
    transform->positionX += velocity->velocityX * deltaTime;
    transform->positionY += velocity->velocityY * deltaTime;
  }
  for (std::uint32_t entityId = 1; entityId < EntityManager::MAX_ENTITY_ID; ++entityId)
  {
    ProjectileComponent *projectile = entityManager.getProjectileComponent(entityId);
    CollisionComponent *collision = entityManager.getCollisionComponent(entityId);
    TransformComponent *transform = entityManager.getTransformComponent(entityId);
    VelocityComponent *velocity = entityManager.getVelocityComponent(entityId);
    if (projectile && collision && transform && velocity)
    {
      float intendedCenterX = transform->positionX + velocity->velocityX * deltaTime;
      float intendedCenterY = transform->positionY + velocity->velocityY * deltaTime;
      bool hit = false;
      for (std::uint32_t otherId = 1; otherId < EntityManager::MAX_ENTITY_ID; ++otherId)
      {
        if (otherId == entityId)
          continue;
        CollisionComponent *otherCollision = entityManager.getCollisionComponent(otherId);
        if (!otherCollision)
          continue;
        if (projectile->ownerId == otherId)
          continue;
        bool overlap =
            collision->getMinX(transform->positionX) + velocity->velocityX * deltaTime < otherCollision->getMaxX(transform->positionX) &&
            collision->getMaxX(transform->positionX) + velocity->velocityX * deltaTime > otherCollision->getMinX(transform->positionX) &&
            collision->getMinY(transform->positionY) + velocity->velocityY * deltaTime < otherCollision->getMaxY(transform->positionY) &&
            collision->getMaxY(transform->positionY) + velocity->velocityY * deltaTime > otherCollision->getMinY(transform->positionY);
        if (overlap)
        {
          hit = true;
          break;
        }
      }
      if (hit)
      {
        entityManager.destroyEntity(entityId);
        continue;
      }
      transform->positionX = intendedCenterX;
      transform->positionY = intendedCenterY;
    }
    else if (transform && velocity && collision && !projectile)
    {
      float previousX = transform->positionX;
      float previousY = transform->positionY;
      float intendedCenterX = previousX + velocity->velocityX * deltaTime;
      float intendedCenterY = previousY + velocity->velocityY * deltaTime;
      transform->positionX = intendedCenterX;
      transform->positionY = intendedCenterY;
      bool blocked = false;
      for (std::uint32_t otherId = 1; otherId < EntityManager::MAX_ENTITY_ID; ++otherId)
      {
        if (otherId == entityId)
          continue;
        CollisionComponent *otherCollision = entityManager.getCollisionComponent(otherId);
        if (!otherCollision)
          continue;
        bool overlap =
            collision->getMinX(transform->positionX) < otherCollision->getMaxX(transform->positionX) &&
            collision->getMaxX(transform->positionX) > otherCollision->getMinX(transform->positionX) &&
            collision->getMinY(transform->positionY) < otherCollision->getMaxY(transform->positionY) &&
            collision->getMaxY(transform->positionY) > otherCollision->getMinY(transform->positionY);
        if (overlap)
        {
          blocked = true;
          break;
        }
      }
      if (blocked)
      {
        transform->positionX = previousX;
        transform->positionY = previousY;
      }
    }
    else if (transform && velocity)
    {
      transform->positionX += velocity->velocityX * deltaTime;
      transform->positionY += velocity->velocityY * deltaTime;
    }
  }
}
