#include "render/renderer.h"
#include "core/camera_service.h"

Renderer::Renderer(CameraService* cameraServicePointer) :
    renderer(nullptr), cameraService(cameraServicePointer) {
}
Renderer::~Renderer() {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
  }
}

bool Renderer::init(SDL_Window* window) {
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (!renderer) {
    return false;
  }

  return true;
}

void Renderer::clear() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void Renderer::present() {
  SDL_RenderPresent(renderer);
}

SDL_Renderer* Renderer::getSDLRenderer() const {
  return renderer;
}

void Renderer::render() {
  SDL_Rect cameraView = cameraService->getViewRectangle();
  // Use cameraView for rendering offset
  // ...existing rendering logic...
}
