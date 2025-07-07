#include "PlayerFactory.h"
#include "../../engine/ecs/components/texture_component.h"
#include "../../engine/ecs/entity_manager.h"
#include "../../engine/ecs/systems/camera_system.h"
#include <stdexcept>

int PlayerFactory::createPlayerEntity(EntityManager& entityManager, float posX, float posY, float speed, int textureId)
{
    int entityId = entityManager.createEntity(EntityTag::Player);
    entityManager.addComponent(entityId, TransformComponent(posX, posY));
    entityManager.addComponent(entityId, VelocityComponent(0.0f, 0.0f));
    entityManager.addComponent(entityId, SpeedComponent(speed));
    entityManager.addComponent(entityId, TextureComponent(textureId));

    return entityId;
}

std::string PlayerFactory::resolvePlayerTexturePath()
{
    return "game/assets/player.png";
}
