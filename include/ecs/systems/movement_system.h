#pragma once
#include <cstdint>
class IMovementSystem {
public:
  virtual ~IMovementSystem()                                         = default;
  virtual void update(float deltaTime, std::uint32_t playerEntityId) = 0;
};
class EntityManager;
class InputHandler;
class MovementSystem : public IMovementSystem {
public:
  MovementSystem(EntityManager* entityManager, InputHandler* inputHandler);
  void                   update(float deltaTime, std::uint32_t playerEntityId) override;
  static constexpr float NORMAL_SPEED = 300.0f;
  static constexpr float SLOW_SPEED   = 150.0f;

private:
  EntityManager* entityManager;
  InputHandler*  inputHandler;
};
