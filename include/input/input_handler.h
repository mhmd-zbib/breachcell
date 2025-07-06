#pragma once
#include "input/input_state.h"
#include <SDL2/SDL.h>

class InputHandler {
public:
  InputHandler();
  ~InputHandler();
  void processInput();
  void handleInput(bool& running);
  // Query if a key is currently pressed
  bool isKeyPressed(SDL_Keycode key) const;

private:
  InputState inputState;
};
