#include "ecs/systems/input_system.h"
#include "input/input_handler.h"
InputSystem &InputSystem::getInstance()
{
  static InputSystem instance;
  return instance;
}
InputSystem::InputSystem() {}
void InputSystem::setRunning(bool &running)
{
  runningPtr = &running;
}
void InputSystem::update()
{
  if (runningPtr)
    InputHandler::getInstance().handleInput(*runningPtr);
}
