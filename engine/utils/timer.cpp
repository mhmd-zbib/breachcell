#include "timer.h"

Timer::Timer() : lastTicks(SDL_GetTicks()) {}

float Timer::getDeltaTime()
{
    Uint32 currentTicks = SDL_GetTicks();
    float deltaTime = (currentTicks - lastTicks) / 1000.0f;
    lastTicks = currentTicks;
    return deltaTime;
}
