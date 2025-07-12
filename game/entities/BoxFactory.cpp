#include "BoxFactory.h"
#include "../../engine/ecs/components/box_component.h"
#include "../../engine/ecs/components/texture_component.h"
#include "../../engine/ecs/components/transform_component.h"
#include "../../engine/ecs/entity_manager.h"

int BoxFactory::createBoxEntity(EntityManager& entityManager, float positionX, float positionY, float width,
                                float height, unsigned char red, unsigned char green, unsigned char blue,
                                unsigned char alpha)
{
    int entityId = entityManager.createEntity(EntityTag::Box);
    entityManager.addComponent(entityId, TransformComponent(positionX, positionY));
    entityManager.addComponent(entityId, BoxComponent(width, height, red, green, blue, alpha));
    return entityId;
}

void BoxFactory::addTextureComponent(EntityManager& entityManager, int entityId, int textureId)
{
    entityManager.addComponent(entityId, TextureComponent(textureId));
}
