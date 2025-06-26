#pragma once
#include <SDL2/SDL.h>
class InputSystem
{
public:
  static InputSystem &getInstance();
  void update();
  void setRunning(bool &running);

private:
  InputSystem();
  bool *runningPtr = nullptr;
};
