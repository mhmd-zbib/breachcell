#ifndef MOUSE_INPUT_H
#define MOUSE_INPUT_H
#include <SDL2/SDL.h>
#include <unordered_map>
class MouseInput
{
  public:
    MouseInput();
    void pollEvents(const SDL_Event& event);
    void nextFrame();
    std::pair<int, int> getMousePosition() const;
    bool isMouseButtonPressed(Uint8 button) const;
    bool isMouseButtonReleased(Uint8 button) const;
    bool isMouseButtonDown(Uint8 button) const;

  private:
    std::unordered_map<Uint8, bool> mouseButtonStates;
    std::unordered_map<Uint8, bool> prevMouseButtonStates;
    int mouseX;
    int mouseY;
};
#endif
