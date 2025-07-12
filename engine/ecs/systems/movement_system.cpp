#include "movement_system.h"
#include "../entity_manager.h"
#include <SDL2/SDL_scancode.h>
#include <cmath>
#include <stdexcept>

namespace
{
float calculateAngleToTarget(float sourceX, float sourceY, float targetX, float targetY)
{
    float dx = targetX - sourceX;
    float dy = targetY - sourceY;
    if (dx == 0.0f && dy == 0.0f)
        return 0.0f;
    return std::atan2(dy, dx) * 180.0f / static_cast<float>(M_PI);
}
} // namespace

void MovementSystem::processInput(InputSystem* inputSystem, int entityId, VelocityComponent* velocityComponent)
{
    if (!inputSystem || !velocityComponent)
        throw std::invalid_argument("Null inputSystem or velocityComponent");
    float velocityX = 0.0f;
    float velocityY = 0.0f;
    auto& keyboard = inputSystem->getKeyboard();
    if (keyboard.isKeyDown(SDL_SCANCODE_W))
        velocityY -= 1.0f;
    if (keyboard.isKeyDown(SDL_SCANCODE_S))
        velocityY += 1.0f;
    if (keyboard.isKeyDown(SDL_SCANCODE_A))
        velocityX -= 1.0f;
    if (keyboard.isKeyDown(SDL_SCANCODE_D))
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
    if (inputSystem)
    {
        auto& mouse = inputSystem->getMouse();
        auto mousePos = mouse.getMousePosition();
        // Mouse position is in screen coordinates; rotation logic should use world coordinates only.
        // For AAA standards, camera offset and mapping are handled in the rendering system.
        float playerX = transform->getPositionX();
        float playerY = transform->getPositionY();
        // If needed, provide a hook for the rendering system to supply mapped mouse world coordinates.
        // For now, set rotation to zero (or retain previous logic if world mouse position is available).
        // transform->setRotation(angle);
    }
}
