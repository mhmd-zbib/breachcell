#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

class ITimer
{
  public:
    virtual ~ITimer() = default;
    virtual float getDeltaTime() = 0;
};

class Timer : public ITimer
{
  public:
    Timer();
    float getDeltaTime() override;

  private:
    Uint32 lastTicks;
};

#endif
