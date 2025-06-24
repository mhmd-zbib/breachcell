#pragma once
#include <SDL2/SDL.h>

class InputHandler
{
public:
  static InputHandler &getInstance();
  void processInput();
  void handleInput(bool &running);

private:
  InputHandler();
  ~InputHandler();
};
