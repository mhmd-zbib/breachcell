#include "input/input_handler.h"
#include <iostream>

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
      pressedKeys.insert(SDL_GetScancodeFromKey(event.key.keysym.sym));
      std::cout << "InputHandler: Key down sym=" << event.key.keysym.sym << " scancode=" << event.key.keysym.scancode << std::endl;
      if (event.key.keysym.sym == SDLK_ESCAPE)
        running = false;
    }
    else if (event.type == SDL_KEYUP)
    {
      pressedKeys.erase(event.key.keysym.sym);
      pressedKeys.erase(SDL_GetScancodeFromKey(event.key.keysym.sym));
      std::cout << "InputHandler: Key up sym=" << event.key.keysym.sym << " scancode=" << event.key.keysym.scancode << std::endl;
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
  bool keycodeFound = pressedKeys.find(key) != pressedKeys.end();
  bool scancodeFound = pressedKeys.find(SDL_GetScancodeFromKey(key)) != pressedKeys.end();
  std::cout << "InputHandler::isKeyPressed key=" << key << " keycodeFound=" << keycodeFound << " scancodeFound=" << scancodeFound << std::endl;
  if (keycodeFound)
    return true;
  if (scancodeFound)
    return true;
  return false;
}

void InputHandler::processInput() {}
