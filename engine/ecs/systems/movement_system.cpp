#include "movement_system.h"
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

void MovementSystem::update(InputSystem* inputSystem, int entityId,
                            std::unordered_map<int, TransformComponent>& transformComponents,
                            std::unordered_map<int, VelocityComponent>& velocityComponents,
                            std::unordered_map<int, SpeedComponent>& speedComponents, float deltaTime)
{
    auto velocityIt = velocityComponents.find(entityId);
    auto transformIt = transformComponents.find(entityId);
    auto speedIt = speedComponents.find(entityId);
    if (velocityIt == velocityComponents.end() || transformIt == transformComponents.end() ||
        speedIt == speedComponents.end())
        throw std::invalid_argument("Missing component for entity");
    processInput(inputSystem, entityId, &velocityIt->second);
    float speed = speedIt->second.getSpeed();
    float velocityX = velocityIt->second.getVelocityX() * speed;
    float velocityY = velocityIt->second.getVelocityY() * speed;
    float newX = transformIt->second.getPositionX() + velocityX * deltaTime;
    float newY = transformIt->second.getPositionY() + velocityY * deltaTime;
    transformIt->second.setPositionX(newX);
    transformIt->second.setPositionY(newY);
}
