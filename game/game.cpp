#include "game.h"
#include "../engine/ecs/components/speed_component.h"
#include "../engine/ecs/systems/movement_system.h"
#include "../engine/ecs/systems/velocity_system.h"
#include "../engine/input/input_system.h"
#include "entities/PlayerFactory.h"

Game::Game() : playerEntityId(1), inputSystem(nullptr) {}

void Game::setInputSystem(InputSystem* inputSystemPtr)
{
    inputSystem = inputSystemPtr;
}

void Game::setMovementSystem(std::shared_ptr<MovementSystem> movementSystemPtr)
{
    movementSystem = movementSystemPtr;
}

void Game::setVelocitySystem(std::shared_ptr<VelocitySystem> velocitySystemPtr)
{
    velocitySystem = velocitySystemPtr;
}

void Game::initialize()
{
    playerEntityId = PlayerFactory::createPlayerEntity(entityManager, 400.0f, 300.0f, 200.0f);
}

void Game::update(float deltaTime)
{
    if (!inputSystem)
        throw std::runtime_error("InputSystem not set");
    if (movementSystem)
        movementSystem->update(inputSystem, playerEntityId, entityManager, deltaTime);
}

void Game::render(Renderer* renderer)
{
    TransformComponent* transform = entityManager.getComponent<TransformComponent>(playerEntityId);
    if (transform)
    {
        CircleShape circle((int) transform->getPositionX(), (int) transform->getPositionY(), 40, 0, 200, 255, 255);
        renderer->getShapeRenderer()->drawShape(&circle, ShapeStyle::Filled);
    }
}

void Game::shutdown()
{
    inputSystem = nullptr;
    movementSystem.reset();
    velocitySystem.reset();
}
