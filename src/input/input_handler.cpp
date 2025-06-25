#include "input/input_handler.h"
#include <iostream>
#include <unordered_set>

InputHandler &InputHandler::getInstance()
{
  static InputHandler instance;
  return instance;
}

InputHandler::InputHandler() {}

InputHandler::~InputHandler() {}

void InputHandler::handleInput(bool &running)
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
      pressedKeys.insert(event.key.keysym.sym);
      std::cout << "Key pressed: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
      if (event.key.keysym.sym == SDLK_ESCAPE)
        running = false;
    }
    else if (event.type == SDL_KEYUP)
    {
      pressedKeys.erase(event.key.keysym.sym);
      std::cout << "Key released: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
    }
    else if (event.type == SDL_MOUSEMOTION)
    {
      std::cout << "Mouse moved to (" << event.motion.x << ", " << event.motion.y << ")" << std::endl;
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
    {
      std::cout << "Mouse button " << (event.type == SDL_MOUSEBUTTONDOWN ? "pressed" : "released")
                << " at (" << event.button.x << ", " << event.button.y << ")" << std::endl;
    }
  }
}

bool InputHandler::isKeyPressed(SDL_Keycode key) const
{
  return pressedKeys.find(key) != pressedKeys.end();
}

void InputHandler::processInput() {}
