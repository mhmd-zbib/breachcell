#include "texture.h"
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <stdexcept>

Texture::Texture(SDL_Renderer* renderer, const std::string& filePath) : texture(nullptr), width(0), height(0)
{
    if (!renderer)
        throw std::invalid_argument("SDL_Renderer pointer is null");
    if (filePath.empty())
        throw std::invalid_argument("Texture file path is empty");

    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface)
    {
        std::fprintf(stderr, "Texture: IMG_Load failed for '%s': %s\n", filePath.c_str(), IMG_GetError());
        throw std::runtime_error("Failed to load image: " + filePath);
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        std::fprintf(stderr, "Texture: SDL_CreateTextureFromSurface failed for '%s': %s\n", filePath.c_str(),
                     SDL_GetError());
        SDL_FreeSurface(surface);
        throw std::runtime_error("Failed to create texture from surface: " + filePath);
    }

    width = surface->w;
    height = surface->h;
    SDL_FreeSurface(surface);
}

Texture::~Texture()
{
    if (texture)
        SDL_DestroyTexture(texture);
}

SDL_Texture* Texture::getNativeTexture() const
{
    return texture;
}

int Texture::getWidth() const
{
    return width;
}

int Texture::getHeight() const
{
    return height;
}
