#include "render/texture_manager.h"
#include <SDL2/SDL_image.h>
#include <stdexcept>
TextureManager &TextureManager::getInstance()
{
  static TextureManager instance;
  return instance;
}
void TextureManager::loadTexture(std::uint32_t textureId, const std::string &filePath, SDL_Renderer *renderer)
{
  if (textures.count(textureId))
    return;
  SDL_Surface *surface = IMG_Load(filePath.c_str());
  if (!surface)
    throw std::runtime_error("TextureManager: Failed to load " + filePath);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  if (!texture)
    throw std::runtime_error("TextureManager: Failed to create texture for " + filePath);
  textures[textureId] = texture;
}
SDL_Texture *TextureManager::getTexture(std::uint32_t textureId) const
{
  auto it = textures.find(textureId);
  if (it == textures.end())
    return nullptr;
  return it->second;
}
void TextureManager::unloadAll()
{
  for (auto &pair : textures)
    if (pair.second)
      SDL_DestroyTexture(pair.second);
  textures.clear();
}
