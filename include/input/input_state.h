#pragma once
#include <set>
#include <SDL2/SDL.h>

class InputState
{
public:
  InputState();
  void addKey(SDL_Keycode key);
  void addScancode(SDL_Scancode scancode);
  void removeKey(SDL_Keycode key);
  void removeScancode(SDL_Scancode scancode);
  bool isKeyActive(SDL_Keycode key) const;
  void clearAll();

private:
  std::set<SDL_Keycode> activeKeycodes;
  std::set<SDL_Scancode> activeScancodes;
};
