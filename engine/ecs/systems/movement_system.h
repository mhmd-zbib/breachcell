#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "../../input/input_system.h"
#include "../components/speed_component.h"
#include "../components/transform_component.h"
#include "../components/velocity_component.h"
#include <unordered_map>

class MovementSystem
{
  public:
    void processInput(InputSystem* inputSystem, int entityId, VelocityComponent* velocityComponent);
    void update(InputSystem* inputSystem, int entityId,
                std::unordered_map<int, TransformComponent>& transformComponents,
                std::unordered_map<int, VelocityComponent>& velocityComponents,
                std::unordered_map<int, SpeedComponent>& speedComponents, float deltaTime);
};

#endif
