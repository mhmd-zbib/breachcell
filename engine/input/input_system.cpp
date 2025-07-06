#include "input_system.h"
#include <iostream>

InputSystem::InputSystem() : quitRequested(false), mouseX(0), mouseY(0) {}

void InputSystem::pollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            quitRequested = true;
        if (event.type == SDL_KEYDOWN)
        {
            keyStates[event.key.keysym.scancode] = true;
            std::cout << "Key pressed: " << SDL_GetScancodeName(event.key.keysym.scancode) << std::endl;
        }
        if (event.type == SDL_KEYUP)
            keyStates[event.key.keysym.scancode] = false;
        if (event.type == SDL_MOUSEBUTTONDOWN)
            mouseButtonStates[event.button.button] = true;
        if (event.type == SDL_MOUSEBUTTONUP)
            mouseButtonStates[event.button.button] = false;
        if (event.type == SDL_MOUSEMOTION)
        {
            mouseX = event.motion.x;
            mouseY = event.motion.y;
        }
    }
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
    {
        bool pressed = state[i];
        auto it = keyStates.find((SDL_Scancode) i);
        if (it != keyStates.end())
            it->second = pressed;
        else if (pressed)
            keyStates[(SDL_Scancode) i] = true;
    }
    Uint32 mouse = SDL_GetMouseState(&mouseX, &mouseY);
    for (Uint8 b = 1; b <= 5; ++b)
    {
        bool pressed = (mouse & SDL_BUTTON(b)) != 0;
        auto it = mouseButtonStates.find(b);
        if (it != mouseButtonStates.end())
            it->second = pressed;
        else if (pressed)
            mouseButtonStates[b] = true;
    }
}

bool InputSystem::shouldQuit() const
{
    return quitRequested;
}

bool InputSystem::isKeyPressed(SDL_Scancode key) const
{
    auto it = keyStates.find(key);
    return it != keyStates.end() && it->second;
}

bool InputSystem::isMouseButtonPressed(Uint8 button) const
{
    auto it = mouseButtonStates.find(button);
    return it != mouseButtonStates.end() && it->second;
}

int InputSystem::getMouseX() const
{
    return mouseX;
}

int InputSystem::getMouseY() const
{
    return mouseY;
}
