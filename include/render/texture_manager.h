#pragma once
#include <SDL2/SDL.h>
#include <cstdint>
#include <string>
#include <unordered_map>
class TextureManager {
public:
  TextureManager();
  ~TextureManager();
  void         loadTexture(std::uint32_t textureId, const std::string& filePath,
                           SDL_Renderer* rendererPointer);
  void         loadTextures(SDL_Renderer* rendererPointer);
  SDL_Texture* getTexture(std::uint32_t textureId) const;
  void         unloadAll();

private:
  std::unordered_map<std::uint32_t, SDL_Texture*> textures;
};
