#include "renderer.h"
#include "shape_renderer.h"
#include "texture.h"
#include "window.h"
#include <SDL2/SDL_image.h>
#include <stdexcept>

Renderer::Renderer(Window* windowInstance)
    : window(windowInstance), renderer(nullptr), initialized(false), camera(nullptr)
{
}

Renderer::~Renderer()
{
    shutdown();
}

bool Renderer::initialize()
{
    if (!window)
        return false;
    renderer = SDL_CreateRenderer(window->getNativeWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
        return false;
    shapeRenderer = std::make_unique<ShapeRenderer>(renderer);
    initialized = true;
    return true;
}

void Renderer::clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);
}

void Renderer::present()
{
    SDL_RenderPresent(renderer);
}

void Renderer::shutdown()
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    shapeRenderer.reset();
    initialized = false;
}

bool Renderer::isInitialized() const
{
    return initialized;
}

void Renderer::drawTexture(const Texture& texture, int x, int y, int w, int h, double angle, SDL_RendererFlip flip,
                           const SDL_Rect* srcRect, Uint8 alpha)
{
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = (w > 0) ? w : texture.getWidth();
    dstRect.h = (h > 0) ? h : texture.getHeight();
    SDL_SetTextureAlphaMod(texture.getNativeTexture(), alpha);
    if (SDL_RenderCopyEx(renderer, texture.getNativeTexture(), srcRect, &dstRect, angle, nullptr, flip) != 0)
    {
        std::fprintf(stderr, "Renderer: SDL_RenderCopyEx failed: %s\n", SDL_GetError());
        throw std::runtime_error("Renderer: SDL_RenderCopyEx failed");
    }
}

std::unique_ptr<Texture> Renderer::loadTexture(const std::string& filePath)
{
    return std::make_unique<Texture>(renderer, filePath);
}

ShapeRenderer* Renderer::getShapeRenderer()
{
    return shapeRenderer.get();
}

SDL_Renderer* Renderer::getSDLRenderer()
{
    return renderer;
}

void Renderer::setCamera(Camera* cameraPtr)
{
    camera = cameraPtr;
}

Camera* Renderer::getCamera()
{
    return camera;
}

void Renderer::setCameraSystem(std::shared_ptr<CameraSystem> cameraSystemPtr)
{
    cameraSystem = cameraSystemPtr;
}
std::shared_ptr<CameraSystem> Renderer::getCameraSystem()
{
    return cameraSystem;
}
