#pragma once
#include <cstdint>
#include <unordered_map>
#include <SDL2/SDL.h>
class RenderSystem
{
public:
  static RenderSystem &getInstance();
  void renderAll();
  void renderAimLine();
  void loadTextures();
  static constexpr int PLAYER_TEXTURE_WIDTH = 64;
  static constexpr int PLAYER_TEXTURE_HEIGHT = 64;

private:
  RenderSystem();
  ~RenderSystem();
  void unloadTextures();
  std::uint32_t playerTextureId;
  std::unordered_map<std::uint32_t, SDL_Texture *> textures;
};
