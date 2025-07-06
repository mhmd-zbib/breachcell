#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <SDL2/SDL.h>

class IInputSystem
{
  public:
    virtual ~IInputSystem() = default;
    virtual void pollEvents() = 0;
    virtual bool shouldQuit() const = 0;
};

class InputSystem : public IInputSystem
{
  public:
    InputSystem();
    void pollEvents() override;
    bool shouldQuit() const override;

  private:
    bool quitRequested;
};

#endif
