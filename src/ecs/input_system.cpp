#include "ecs/systems/input_system.h"
#include "input/input_handler.h"

InputSystem::InputSystem(InputHandler* handler) :
    runningFlagPointer(nullptr), inputHandler(handler) {
}

void InputSystem::update() {
  if (runningFlagPointer && inputHandler)
    inputHandler->handleInput(*runningFlagPointer);
}

void InputSystem::setRunning(bool& runningFlag) {
  runningFlagPointer = &runningFlag;
}
