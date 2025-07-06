#include "renderer.h"
#include "shape_renderer.h"
#include "texture.h"
#include "window.h"
#include <SDL2/SDL_image.h>
#include <stdexcept>

Renderer::Renderer(Window* windowInstance) : window(windowInstance), renderer(nullptr), initialized(false) {}

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

void Renderer::drawTexture(const Texture& texture, int x, int y, int w, int h, double angle, SDL_RendererFlip flip)
{
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = (w > 0) ? w : texture.getWidth();
    dstRect.h = (h > 0) ? h : texture.getHeight();
    SDL_RenderCopyEx(renderer, texture.getNativeTexture(), nullptr, &dstRect, angle, nullptr, flip);
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
