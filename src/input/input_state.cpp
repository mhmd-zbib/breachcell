#include "input/input_state.h"

InputState::InputState() {}

void InputState::addKey(SDL_Keycode key)
{
  activeKeycodes.insert(key);
}

void InputState::addScancode(SDL_Scancode scancode)
{
  activeScancodes.insert(scancode);
}

void InputState::removeKey(SDL_Keycode key)
{
  activeKeycodes.erase(key);
}

void InputState::removeScancode(SDL_Scancode scancode)
{
  activeScancodes.erase(scancode);
}

bool InputState::isKeyActive(SDL_Keycode key) const
{
  if (activeKeycodes.find(key) != activeKeycodes.end())
    return true;
  if (activeScancodes.find(SDL_GetScancodeFromKey(key)) != activeScancodes.end())
    return true;
  return false;
}

void InputState::clearAll()
{
  activeKeycodes.clear();
  activeScancodes.clear();
}
