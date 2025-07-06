#pragma once
#include <SDL2/SDL.h>
class InputSystem
{
public:
  static InputSystem& getInstance();
  void update();
  void setRunning(bool& runningFlag);

private:
  InputSystem();
  InputSystem(const InputSystem&) = delete;
  InputSystem& operator=(const InputSystem&) = delete;
  bool* runningFlagPointer = nullptr;
};
