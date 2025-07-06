#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <SDL2/SDL.h>
#include <unordered_map>

class IInputSystem
{
  public:
    virtual ~IInputSystem() = default;
    virtual void pollEvents() = 0;
    virtual bool shouldQuit() const = 0;
    virtual bool isKeyPressed(SDL_Scancode key) const = 0;
    virtual bool isMouseButtonPressed(Uint8 button) const = 0;
    virtual int getMouseX() const = 0;
    virtual int getMouseY() const = 0;
};

class InputSystem : public IInputSystem
{
  public:
    InputSystem();
    void pollEvents() override;
    bool shouldQuit() const override;
    bool isKeyPressed(SDL_Scancode key) const override;
    bool isMouseButtonPressed(Uint8 button) const override;
    int getMouseX() const override;
    int getMouseY() const override;

  private:
    bool quitRequested;
    std::unordered_map<SDL_Scancode, bool> keyStates;
    std::unordered_map<Uint8, bool> mouseButtonStates;
    int mouseX;
    int mouseY;
};

#endif
