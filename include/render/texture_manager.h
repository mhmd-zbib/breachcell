#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>
class TextureManager
{
public:
  static TextureManager &getInstance();
  void loadTexture(std::uint32_t textureId, const std::string &filePath, SDL_Renderer *renderer);
  SDL_Texture *getTexture(std::uint32_t textureId) const;
  void unloadAll();

private:
  TextureManager() = default;
  TextureManager(const TextureManager &) = delete;
  TextureManager &operator=(const TextureManager &) = delete;
  std::unordered_map<std::uint32_t, SDL_Texture *> textures;
};
