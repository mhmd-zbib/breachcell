#pragma once
#include <SDL2/SDL.h>
#include <unordered_set>

class InputHandler
{
public:
  static InputHandler &getInstance();
  void processInput();
  void handleInput(bool &running);
  // Query if a key is currently pressed
  bool isKeyPressed(SDL_Keycode key) const;

private:
  InputHandler();
  ~InputHandler();

  std::unordered_set<SDL_Keycode> pressedKeys;
};
