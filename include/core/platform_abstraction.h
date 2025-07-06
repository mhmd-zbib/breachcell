#pragma once
#include <SDL2/SDL.h>
#include <string>

class PlatformAbstraction {
public:
  PlatformAbstraction();
  ~PlatformAbstraction();
  void        initializeSDL();
  void        shutdownSDL();
  void        createWindow(const std::string& windowTitle, int windowWidth, int windowHeight);
  void        destroyWindow();
  SDL_Window* getWindow() const;
  void        getWindowSize(int& windowWidth, int& windowHeight) const;

private:
  SDL_Window* window;
};
