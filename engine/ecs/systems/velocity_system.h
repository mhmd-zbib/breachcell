#ifndef VELOCITY_SYSTEM_H
#define VELOCITY_SYSTEM_H

#include "../components/transform_component.h"
#include "../components/velocity_component.h"

class VelocitySystem
{
  public:
    void update(TransformComponent* transform, VelocityComponent* velocity, float deltaTime);
};

#endif
