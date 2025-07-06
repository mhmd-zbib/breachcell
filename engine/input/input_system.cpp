#include "input_system.h"
#include <SDL2/SDL.h>
#include <iostream>

InputSystem::InputSystem() : quitRequested(false) {}

void InputSystem::pollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            quitRequested = true;
        keyboard.pollEvents(event);
        mouse.pollEvents(event);
    }
}

void InputSystem::nextFrame()
{
    keyboard.nextFrame();
    mouse.nextFrame();
}

KeyboardInput& InputSystem::getKeyboard()
{
    return keyboard;
}

MouseInput& InputSystem::getMouse()
{
    return mouse;
}

bool InputSystem::shouldQuit() const
{
    return quitRequested;
}
