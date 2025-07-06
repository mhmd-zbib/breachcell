#include "velocity_system.h"

void VelocitySystem::update(TransformComponent* transform, VelocityComponent* velocity, float deltaTime)
{
    if (!transform || !velocity)
        return;
    float newPositionX = transform->getPositionX() + velocity->getVelocityX() * deltaTime;
    float newPositionY = transform->getPositionY() + velocity->getVelocityY() * deltaTime;
    transform->setPositionX(newPositionX);
    transform->setPositionY(newPositionY);
}
