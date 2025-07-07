#pragma once

#include "../graphics/texture.h"
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <unordered_map>

class TextureManager
{
  public:
    explicit TextureManager(SDL_Renderer* sdlRenderer);
    int loadTexture(const std::string& textureKey, const std::string& filePath);
    Texture* getTexture(int textureId) const;
    void unloadTexture(int textureId);
    void clear();

    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

  private:
    SDL_Renderer* renderer;
    std::unordered_map<int, std::unique_ptr<Texture>> textureMap;
    std::unordered_map<std::string, int> keyToIdMap;
    int nextId;
};
