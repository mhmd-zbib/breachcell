#pragma once
#include <SDL2/SDL.h>
#include "input/input_state.h"

class InputHandler
{
public:
  static InputHandler& getInstance();
  void processInput();
  void handleInput(bool& running);
  // Query if a key is currently pressed
  bool isKeyPressed(SDL_Keycode key) const;

private:
  InputHandler();
  ~InputHandler();
  InputState inputState;
};
