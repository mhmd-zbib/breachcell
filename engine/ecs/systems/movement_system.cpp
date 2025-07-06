#include "movement_system.h"
#include "../entity_manager.h"
#include <SDL2/SDL_scancode.h>
#include <cmath>
#include <stdexcept>

void MovementSystem::processInput(InputSystem* inputSystem, int entityId, VelocityComponent* velocityComponent)
{
    if (!inputSystem || !velocityComponent)
        throw std::invalid_argument("Null inputSystem or velocityComponent");
    float velocityX = 0.0f;
    float velocityY = 0.0f;
    if (inputSystem->isKeyPressed(SDL_SCANCODE_W))
        velocityY -= 1.0f;
    if (inputSystem->isKeyPressed(SDL_SCANCODE_S))
        velocityY += 1.0f;
    if (inputSystem->isKeyPressed(SDL_SCANCODE_A))
        velocityX -= 1.0f;
    if (inputSystem->isKeyPressed(SDL_SCANCODE_D))
        velocityX += 1.0f;
    float length = std::sqrt(velocityX * velocityX + velocityY * velocityY);
    if (length > 0.0f)
    {
        velocityX /= length;
        velocityY /= length;
    }
    velocityComponent->setVelocityX(velocityX);
    velocityComponent->setVelocityY(velocityY);
}

void MovementSystem::update(InputSystem* inputSystem, int entityId, EntityManager& entityManager, float deltaTime)
{
    VelocityComponent* velocity = entityManager.getComponent<VelocityComponent>(entityId);
    TransformComponent* transform = entityManager.getComponent<TransformComponent>(entityId);
    SpeedComponent* speed = entityManager.getComponent<SpeedComponent>(entityId);
    if (!velocity || !transform || !speed)
        throw std::invalid_argument("Missing component for entity");
    processInput(inputSystem, entityId, velocity);
    float s = speed->getSpeed();
    float velocityX = velocity->getVelocityX() * s;
    float velocityY = velocity->getVelocityY() * s;
    float newX = transform->getPositionX() + velocityX * deltaTime;
    float newY = transform->getPositionY() + velocityY * deltaTime;
    transform->setPositionX(newX);
    transform->setPositionY(newY);
}
