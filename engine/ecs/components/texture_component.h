#pragma once
#include <string>

class TextureComponent
{
  public:
    explicit TextureComponent(int textureId);
    int getTextureId() const;

  private:
    int textureId;
};
