#pragma once
#include "../../graphics/renderer.h"
#include "../../resources/texture_manager.h"
#include "../components/transform_component.h"
#include "../entity_manager.h"

class TextureRenderSystem
{
  public:
    explicit TextureRenderSystem(TextureManager* textureManager);
    void render(EntityManager& entityManager, Renderer* renderer);

  private:
    TextureManager* textureManager;
};
