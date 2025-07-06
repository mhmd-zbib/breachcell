#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H
#include <SDL2/SDL.h>
#include <unordered_map>
class KeyboardInput
{
  public:
    KeyboardInput();
    void pollEvents(const SDL_Event& event);
    bool isKeyPressed(SDL_Scancode key) const;
    bool isKeyReleased(SDL_Scancode key) const;
    bool isKeyDown(SDL_Scancode key) const;
    void nextFrame();

  private:
    std::unordered_map<SDL_Scancode, bool> keyStates;
    std::unordered_map<SDL_Scancode, bool> prevKeyStates;
};
#endif
