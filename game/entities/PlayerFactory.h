#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

#include <string>

#include "../../engine/ecs/components/speed_component.h"
#include "../../engine/ecs/components/transform_component.h"
#include "../../engine/ecs/components/velocity_component.h"
#include "../../engine/ecs/entity_manager.h"
#include "../../engine/ecs/systems/camera_system.h"
#include "../../engine/resources/texture_manager.h"

class PlayerFactory
{
  public:
    static int createPlayerEntity(EntityManager& entityManager, float posX, float posY, float speed, int textureId);
    static void addRequiredTag(EntityManager& entityManager, int entityId, const std::string& tagValue);
    static std::string resolvePlayerTexturePath();
};

#endif
