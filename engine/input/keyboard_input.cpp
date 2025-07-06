#include "keyboard_input.h"
KeyboardInput::KeyboardInput() {}
void KeyboardInput::pollEvents(const SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN)
        keyStates[event.key.keysym.scancode] = true;
    if (event.type == SDL_KEYUP)
        keyStates[event.key.keysym.scancode] = false;
}
bool KeyboardInput::isKeyPressed(SDL_Scancode key) const
{
    auto it = keyStates.find(key);
    auto prev = prevKeyStates.find(key);
    return it != keyStates.end() && it->second && (prev == prevKeyStates.end() || !prev->second);
}
bool KeyboardInput::isKeyReleased(SDL_Scancode key) const
{
    auto it = keyStates.find(key);
    auto prev = prevKeyStates.find(key);
    return prev != prevKeyStates.end() && prev->second && (it == keyStates.end() || !it->second);
}
bool KeyboardInput::isKeyDown(SDL_Scancode key) const
{
    auto it = keyStates.find(key);
    return it != keyStates.end() && it->second;
}
void KeyboardInput::nextFrame()
{
    prevKeyStates = keyStates;
}
