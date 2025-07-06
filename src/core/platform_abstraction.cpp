#include "core/platform_abstraction.h"
#include <stdexcept>

PlatformAbstraction::PlatformAbstraction() : window(nullptr) {
}

PlatformAbstraction::~PlatformAbstraction() {
  destroyWindow();
  shutdownSDL();
}

void PlatformAbstraction::initializeSDL() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw std::runtime_error("SDL initialization failed");
  }
}

void PlatformAbstraction::shutdownSDL() {
  SDL_Quit();
}

void PlatformAbstraction::createWindow(const std::string& windowTitle, int windowWidth,
                                       int windowHeight) {
  window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (!window) {
    throw std::runtime_error("Window creation failed");
  }
}

void PlatformAbstraction::destroyWindow() {
  if (window) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }
}

SDL_Window* PlatformAbstraction::getWindow() const {
  return window;
}

void PlatformAbstraction::getWindowSize(int& windowWidth, int& windowHeight) const {
  if (!window) {
    windowWidth  = 0;
    windowHeight = 0;
    return;
  }
  SDL_GetWindowSize(window, &windowWidth, &windowHeight);
}
