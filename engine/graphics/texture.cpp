#include "texture.h"
#include <SDL2/SDL_image.h>
#include <stdexcept>

Texture::Texture(SDL_Renderer* renderer, const std::string& filePath) : texture(nullptr), width(0), height(0)
{
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface)
        throw std::runtime_error("Failed to load image: " + filePath);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
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
