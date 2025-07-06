#pragma once
#include <SDL2/SDL.h>
#include <string>

class PlatformAbstraction {
public:
  static PlatformAbstraction& getInstance();
  void                        initializeSDL();
  void                        shutdownSDL();
  void        createWindow(const std::string& windowTitle, int windowWidth, int windowHeight);
  void        destroyWindow();
  SDL_Window* getWindow() const;
  void        getWindowSize(int& windowWidth, int& windowHeight) const;

private:
  PlatformAbstraction();
  ~PlatformAbstraction();
  PlatformAbstraction(const PlatformAbstraction&)            = delete;
  PlatformAbstraction& operator=(const PlatformAbstraction&) = delete;
  SDL_Window*          window;
};
