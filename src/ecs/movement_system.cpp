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
    if (inputHandler.isKeyPressed(SDLK_w) || inputHandler.isKeyPressed(SDL_SCANCODE_W))
      velocity->velocityY = -1.0f;
    if (inputHandler.isKeyPressed(SDLK_s) || inputHandler.isKeyPressed(SDL_SCANCODE_S))
      velocity->velocityY = 1.0f;
    if (inputHandler.isKeyPressed(SDLK_a) || inputHandler.isKeyPressed(SDL_SCANCODE_A))
      velocity->velocityX = -1.0f;
    if (inputHandler.isKeyPressed(SDLK_d) || inputHandler.isKeyPressed(SDL_SCANCODE_D))
      velocity->velocityX = 1.0f;
    std::printf("MovementSystem::update velocity: %.2f, %.2f\n", velocity->velocityX, velocity->velocityY);
    float magnitude = std::sqrt(velocity->velocityX * velocity->velocityX + velocity->velocityY * velocity->velocityY);
    if (magnitude > 0.0f)
    {
      velocity->velocityX = (velocity->velocityX / magnitude) * speed;
      velocity->velocityY = (velocity->velocityY / magnitude) * speed;
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

void MovementSystem::update()
{
  static Uint32 lastTicks = SDL_GetTicks();
  Uint32 currentTicks = SDL_GetTicks();
  float deltaTime = (currentTicks - lastTicks) / 1000.0f;
  lastTicks = currentTicks;
  update(deltaTime);
}
