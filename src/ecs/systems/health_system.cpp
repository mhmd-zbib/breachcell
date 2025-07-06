#include "ecs/systems/health_system.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
HealthSystem& HealthSystem::getInstance()
{
  static HealthSystem instance;
  return instance;
}
HealthSystem::HealthSystem() {}
void HealthSystem::update()
{
  EntityManager& entityManager = EntityManager::getInstance();

  for (std::uint32_t entityId = 1; entityId < EntityManager::MAX_ENTITY_ID; ++entityId)
  {
    HealthComponent* health = entityManager.getHealthComponent(entityId);

    if (!health)
    {
      continue;
    }

    if (health->getValue() <= health->getMinValue())
    {
      entityManager.destroyEntity(entityId);
    }
  }
}
