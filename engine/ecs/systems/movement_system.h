#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "../../input/input_system.h"
#include "../components/speed_component.h"
#include "../components/transform_component.h"
#include "../components/velocity_component.h"
#include "../entity_manager.h"
#include <unordered_map>

class MovementSystem
{
  public:
    void processInput(InputSystem* inputSystem, int entityId, VelocityComponent* velocityComponent);
    void update(InputSystem* inputSystem, int entityId, EntityManager& entityManager, float deltaTime);
};

#endif
