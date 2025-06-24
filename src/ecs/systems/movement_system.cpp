#include "ecs/systems/movement_system.h"
#include "ecs/entity_manager.h"
MovementSystem &MovementSystem::getInstance()
{
  static MovementSystem instance;
  return instance;
}
MovementSystem::MovementSystem() {}
void MovementSystem::update(float deltaTime)
{
  EntityManager &entityManager = EntityManager::getInstance();
  for (std::uint32_t entityId = 1; entityId < UINT32_MAX; ++entityId)
  {
    auto velocity = entityManager.getVelocityComponent(entityId);
    auto transform = entityManager.getTransformComponent(entityId);
    if (velocity && transform)
    {
      transform->positionX += velocity->velocityX * deltaTime;
      transform->positionY += velocity->velocityY * deltaTime;
    }
  }
}
