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
      float intendedX = transform->positionX + velocity->velocityX * deltaTime;
      float intendedY = transform->positionY + velocity->velocityY * deltaTime;
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
        bool overlap = intendedX < otherCollision->boxX + otherCollision->boxWidth &&
                       intendedX + collision->boxWidth > otherCollision->boxX &&
                       intendedY < otherCollision->boxY + otherCollision->boxHeight &&
                       intendedY + collision->boxHeight > otherCollision->boxY;
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
      transform->positionX = intendedX;
      transform->positionY = intendedY;
      collision->boxX = transform->positionX;
      collision->boxY = transform->positionY;
    }
    else if (transform && velocity && collision && !projectile)
    {
      float previousX = transform->positionX;
      float previousY = transform->positionY;
      transform->positionX += velocity->velocityX * deltaTime;
      transform->positionY += velocity->velocityY * deltaTime;
      collision->boxX = transform->positionX;
      collision->boxY = transform->positionY;
      bool blocked = false;
      for (std::uint32_t otherId = 1; otherId < EntityManager::MAX_ENTITY_ID; ++otherId)
      {
        if (otherId == entityId)
          continue;
        CollisionComponent *otherCollision = entityManager.getCollisionComponent(otherId);
        if (!otherCollision)
          continue;
        bool overlap = collision->boxX < otherCollision->boxX + otherCollision->boxWidth &&
                       collision->boxX + collision->boxWidth > otherCollision->boxX &&
                       collision->boxY < otherCollision->boxY + otherCollision->boxHeight &&
                       collision->boxY + collision->boxHeight > otherCollision->boxY;
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
        collision->boxX = previousX;
        collision->boxY = previousY;
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
