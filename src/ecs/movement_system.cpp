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

void MovementSystem::setPlayerEntityId(std::uint32_t id)
{
  playerEntityId = id;
}

void MovementSystem::update(float deltaTime)
{
  EntityManager &entityManager = EntityManager::getInstance();
  InputHandler &inputHandler = InputHandler::getInstance();
  auto velocity = entityManager.getVelocityComponent(playerEntityId);
  auto transform = entityManager.getTransformComponent(playerEntityId);
  if (velocity && transform)
  {
    velocity->velocityX = 0.0f;
    velocity->velocityY = 0.0f;

    float speed = inputHandler.isKeyPressed(SDLK_LSHIFT) || inputHandler.isKeyPressed(SDLK_RSHIFT) ? SLOW_SPEED : NORMAL_SPEED;
    if (inputHandler.isKeyPressed(SDLK_w))
      velocity->velocityY = -1.0f;
    if (inputHandler.isKeyPressed(SDLK_s))
      velocity->velocityY = 1.0f;
    if (inputHandler.isKeyPressed(SDLK_a))
      velocity->velocityX = -1.0f;
    if (inputHandler.isKeyPressed(SDLK_d))
      velocity->velocityX = 1.0f;

    float magnitude = std::sqrt(velocity->velocityX * velocity->velocityX + velocity->velocityY * velocity->velocityY);
    if (magnitude > 0.0f)
    {
      velocity->velocityX = (velocity->velocityX / magnitude) * speed;
      velocity->velocityY = (velocity->velocityY / magnitude) * speed;
    }
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
            collision->getMinX() + velocity->velocityX * deltaTime < otherCollision->getMaxX() &&
            collision->getMaxX() + velocity->velocityX * deltaTime > otherCollision->getMinX() &&
            collision->getMinY() + velocity->velocityY * deltaTime < otherCollision->getMaxY() &&
            collision->getMaxY() + velocity->velocityY * deltaTime > otherCollision->getMinY();
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
      collision->centerX = intendedCenterX;
      collision->centerY = intendedCenterY;
    }
    else if (transform && velocity && collision && !projectile)
    {
      float previousX = transform->positionX;
      float previousY = transform->positionY;
      float intendedCenterX = previousX + velocity->velocityX * deltaTime;
      float intendedCenterY = previousY + velocity->velocityY * deltaTime;
      collision->centerX = intendedCenterX;
      collision->centerY = intendedCenterY;
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
            collision->getMinX() < otherCollision->getMaxX() &&
            collision->getMaxX() > otherCollision->getMinX() &&
            collision->getMinY() < otherCollision->getMaxY() &&
            collision->getMaxY() > otherCollision->getMinY();
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
        collision->centerX = previousX;
        collision->centerY = previousY;
      }
    }
    else if (transform && velocity)
    {
      transform->positionX += velocity->velocityX * deltaTime;
      transform->positionY += velocity->velocityY * deltaTime;
    }
  }
}

void MovementSystem::update()
{
  static Uint32 lastTicks = SDL_GetTicks();
  Uint32 currentTicks = SDL_GetTicks();
  float deltaTime = (currentTicks - lastTicks) / 1000.0f;
  lastTicks = currentTicks;
  update(deltaTime);
}
