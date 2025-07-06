#include "input_system.h"

InputSystem::InputSystem() : quitRequested(false) {}

void InputSystem::pollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            quitRequested = true;
    }
}

bool InputSystem::shouldQuit() const
{
    return quitRequested;
}
