#include "game.h"
#include "../engine/ecs/components/speed_component.h"
#include "../engine/ecs/systems/camera_system.h"
#include "../engine/ecs/systems/movement_system.h"
#include "../engine/ecs/systems/velocity_system.h"
#include "../engine/graphics/rectangle_shape.h"
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

void Game::setCameraSystem(std::shared_ptr<CameraSystem> cameraSystemPtr)
{
    cameraSystem = cameraSystemPtr;
}

void Game::initialize()
{
    playerEntityId = PlayerFactory::createPlayerEntity(entityManager, 400.0f, 300.0f, 200.0f, cameraSystem.get());
}

void Game::update(float deltaTime)
{
    if (!inputSystem)
        throw std::runtime_error("InputSystem not set");
    inputSystem->nextFrame();
    if (movementSystem)
        movementSystem->update(inputSystem, playerEntityId, entityManager, deltaTime);
}

void Game::render(Renderer* renderer)
{
    TransformComponent* transform = entityManager.getComponent<TransformComponent>(playerEntityId);
    if (transform && cameraSystem)
    {
        CameraComponent* camera = cameraSystem->getCameraComponent();
        float screenX = transform->getPositionX() - camera->getPositionX();
        float screenY = transform->getPositionY() - camera->getPositionY();
        CircleShape circle((int) screenX, (int) screenY, 40, 0, 200, 255, 255);
        renderer->getShapeRenderer()->drawShape(&circle, ShapeStyle::Filled);
        int boxWidth = 60;
        int boxHeight = 60;
        int boxWorldX = 100;
        int boxWorldY = 100;
        float boxScreenX = boxWorldX - camera->getPositionX();
        float boxScreenY = boxWorldY - camera->getPositionY();
        RectangleShape box((int) boxScreenX, (int) boxScreenY, boxWidth, boxHeight, 255, 0, 0, 255);
        renderer->getShapeRenderer()->drawShape(&box, ShapeStyle::Filled);
    }
}

void Game::shutdown()
{
    inputSystem = nullptr;
    movementSystem.reset();
    velocitySystem.reset();
}

EntityManager& Game::getEntityManager()
{
    return entityManager;
}
