#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <string>

class Texture
{
  public:
    Texture(SDL_Renderer* renderer, const std::string& filePath);
    ~Texture();
    SDL_Texture* getNativeTexture() const;
    int getWidth() const;
    int getHeight() const;

  private:
    SDL_Texture* texture;
    int width;
    int height;
};

#endif
