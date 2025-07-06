#ifndef GAME_H
#define GAME_H

#include "../engine/core/igame.h"
#include "../engine/ecs/components/speed_component.h"
#include "../engine/ecs/components/transform_component.h"
#include "../engine/ecs/components/velocity_component.h"
#include "../engine/ecs/systems/movement_system.h"
#include "../engine/ecs/systems/velocity_system.h"
#include "../engine/graphics/circle_shape.h"
#include "../engine/graphics/renderer.h"
#include "../engine/graphics/shape_renderer.h"
#include "../engine/input/input_system.h"
#include "entities/PlayerFactory.h"
#include <memory>
#include <stdexcept>
#include <unordered_map>

class IInputInjectable
{
  public:
    virtual void setInputSystem(InputSystem* inputSystemPtr) = 0;
    virtual ~IInputInjectable() = default;
};

class Game : public IGame, public IInputInjectable
{
  public:
    Game();
    void initialize() override;
    void update(float deltaTime) override;
    void render(Renderer* renderer) override;
    void shutdown() override;
    void setInputSystem(InputSystem* inputSystemPtr) override;
    void setMovementSystem(std::shared_ptr<MovementSystem> movementSystemPtr);
    void setVelocitySystem(std::shared_ptr<VelocitySystem> velocitySystemPtr);

  private:
    int playerEntityId;
    std::unordered_map<int, TransformComponent> transformComponents;
    std::unordered_map<int, VelocityComponent> velocityComponents;
    std::unordered_map<int, SpeedComponent> speedComponents;
    InputSystem* inputSystem;
    std::shared_ptr<MovementSystem> movementSystem;
    std::shared_ptr<VelocitySystem> velocitySystem;
};

#endif