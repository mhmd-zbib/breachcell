#include <iostream>
#include "input/input_handler.h"
#include "input/input_state.h"

InputHandler& InputHandler::getInstance()
{
  static InputHandler instance;
  return instance;
}

InputHandler::InputHandler() {}

InputHandler::~InputHandler() {}

void InputHandler::handleInput(bool& running)
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      running = false;
    }
    else if (event.type == SDL_KEYDOWN)
    {
      inputState.addKey(event.key.keysym.sym);
      inputState.addScancode(SDL_GetScancodeFromKey(event.key.keysym.sym));

      if (event.key.keysym.sym == SDLK_ESCAPE)
      {
        running = false;
      }
    }
    else if (event.type == SDL_KEYUP)
    {
      inputState.removeKey(event.key.keysym.sym);
      inputState.removeScancode(SDL_GetScancodeFromKey(event.key.keysym.sym));
    }
    else if (event.type == SDL_MOUSEMOTION)
    {
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
    {
    }
  }
}

bool InputHandler::isKeyPressed(SDL_Keycode key) const
{
  bool result = inputState.isKeyActive(key);
  return result;
}

void InputHandler::processInput() {}
