#pragma once
#include <SDL2/SDL.h>
class CameraService;
class Renderer {
public:
  Renderer(CameraService* cameraServicePointer);
  ~Renderer();
  bool          init(SDL_Window* window);
  void          clear();
  void          present();
  SDL_Renderer* getSDLRenderer() const;
  void          render();

private:
  SDL_Renderer*  renderer;
  CameraService* cameraService;
};
