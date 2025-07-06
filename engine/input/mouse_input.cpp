#include "mouse_input.h"
MouseInput::MouseInput() : mouseX(0), mouseY(0) {}
void MouseInput::pollEvents(const SDL_Event& event)
{
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
void MouseInput::nextFrame()
{
    prevMouseButtonStates = mouseButtonStates;
}
std::pair<int, int> MouseInput::getMousePosition() const
{
    return {mouseX, mouseY};
}
bool MouseInput::isMouseButtonPressed(Uint8 button) const
{
    auto it = mouseButtonStates.find(button);
    auto prev = prevMouseButtonStates.find(button);
    return it != mouseButtonStates.end() && it->second && (prev == prevMouseButtonStates.end() || !prev->second);
}
bool MouseInput::isMouseButtonReleased(Uint8 button) const
{
    auto it = mouseButtonStates.find(button);
    auto prev = prevMouseButtonStates.find(button);
    return prev != prevMouseButtonStates.end() && prev->second && (it == mouseButtonStates.end() || !it->second);
}
bool MouseInput::isMouseButtonDown(Uint8 button) const
{
    auto it = mouseButtonStates.find(button);
    return it != mouseButtonStates.end() && it->second;
}
