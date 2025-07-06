#include "PlayerFactory.h"
#include "../../engine/ecs/components/speed_component.h"

int PlayerFactory::createPlayerEntity(int nextEntityId,
                                      std::unordered_map<int, TransformComponent>& transformComponents,
                                      std::unordered_map<int, VelocityComponent>& velocityComponents,
                                      std::unordered_map<int, SpeedComponent>& speedComponents, float posX, float posY,
                                      float speed)
{
    transformComponents[nextEntityId] = TransformComponent(posX, posY);
    velocityComponents[nextEntityId] = VelocityComponent(0.0f, 0.0f);
    speedComponents[nextEntityId] = SpeedComponent(speed);
    return nextEntityId;
}
