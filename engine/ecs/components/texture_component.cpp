#include "texture_component.h"

TextureComponent::TextureComponent(int id) : textureId(id) {}

int TextureComponent::getTextureId() const
{
    return textureId;
}
