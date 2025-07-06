#include "PlayerFactory.h"
#include "../../engine/ecs/entity_manager.h"

int PlayerFactory::createPlayerEntity(EntityManager& entityManager, float posX, float posY, float speed)
{
    int entityId = entityManager.createEntity(EntityTag::Player);
    entityManager.addComponent(entityId, TransformComponent(posX, posY));
    entityManager.addComponent(entityId, VelocityComponent(0.0f, 0.0f));
    entityManager.addComponent(entityId, SpeedComponent(speed));
    return entityId;
}
