#include "ecs/systems/health_system.h"
#include "ecs/components.h"
#include "ecs/entity_manager.h"

HealthSystem::HealthSystem(EntityManager* entityManagerPtr) : entityManager(entityManagerPtr) {
}

void HealthSystem::update() {
  if (!entityManager)
    return;

  for (std::uint32_t entityId = 1; entityId < EntityManager::MAX_ENTITY_ID; ++entityId) {
    HealthComponent* health = entityManager->getHealthComponent(entityId);

    if (!health) {
      continue;
    }

    if (health->getValue() <= health->getMinValue()) {
      entityManager->destroyEntity(entityId);
    }
  }
}
