#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <memory>
#include <string>

class Window;
class Texture;
class ShapeRenderer;
class Camera;
class CameraSystem;

class Renderer
{
  public:
    Renderer(Window* windowInstance);
    ~Renderer();
    bool initialize();
    void clear(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255);
    void present();
    void shutdown();
    bool isInitialized() const;
    void drawTexture(const Texture& texture, int x, int y, int w = -1, int h = -1, double angle = 0.0,
                     SDL_RendererFlip flip = SDL_FLIP_NONE, const SDL_Rect* srcRect = nullptr, Uint8 alpha = 255);
    std::unique_ptr<Texture> loadTexture(const std::string& filePath);
    ShapeRenderer* getShapeRenderer();
    SDL_Renderer* getSDLRenderer();
    void setCamera(Camera* cameraPtr);
    Camera* getCamera();
    void setCameraSystem(std::shared_ptr<CameraSystem> cameraSystemPtr);
    std::shared_ptr<CameraSystem> getCameraSystem();

  private:
    Window* window;
    SDL_Renderer* renderer;
    std::unique_ptr<ShapeRenderer> shapeRenderer;
    bool initialized;
    Camera* camera;
    std::shared_ptr<CameraSystem> cameraSystem;
};

#endif
