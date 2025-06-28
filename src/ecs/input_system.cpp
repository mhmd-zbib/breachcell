#include "ecs/systems/input_system.h"
#include "input/input_handler.h"
InputSystem &InputSystem::getInstance()
{
  static InputSystem instance;
  return instance;
}
InputSystem::InputSystem() {}
void InputSystem::setRunning(bool &runningFlag)
{
  runningFlagPointer = &runningFlag;
}
void InputSystem::update()
{
  if (runningFlagPointer)
    InputHandler::getInstance().handleInput(*runningFlagPointer);
}
