#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include "keyboard_input.h"
#include "mouse_input.h"
#include <SDL2/SDL.h>

class InputSystem
{
  public:
    InputSystem();
    void pollEvents();
    void nextFrame();
    KeyboardInput& getKeyboard();
    MouseInput& getMouse();
    bool shouldQuit() const;

  private:
    KeyboardInput keyboard;
    MouseInput mouse;
    bool quitRequested;
};

#endif
