#ifndef BOX_FACTORY_H
#define BOX_FACTORY_H

#include "../../engine/ecs/components/box_component.h"
#include "../../engine/ecs/components/transform_component.h"
#include "../../engine/ecs/entity_manager.h"
#include "../../engine/ecs/systems/camera_system.h"

class BoxFactory
{
  public:
    static int createBoxEntity(EntityManager& entityManager, float positionX, float positionY, float width,
                               float height, unsigned char red, unsigned char green, unsigned char blue,
                               unsigned char alpha = 255);
};

#endif
