#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

#include "../../engine/ecs/components/speed_component.h"
#include "../../engine/ecs/components/transform_component.h"
#include "../../engine/ecs/components/velocity_component.h"
#include <unordered_map>

class PlayerFactory
{
  public:
    static int createPlayerEntity(int nextEntityId, std::unordered_map<int, TransformComponent>& transformComponents,
                                  std::unordered_map<int, VelocityComponent>& velocityComponents,
                                  std::unordered_map<int, SpeedComponent>& speedComponents, float posX, float posY,
                                  float speed);
};

#endif
