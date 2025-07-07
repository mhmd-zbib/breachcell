#ifndef GAME_H
#define GAME_H

#include "../engine/core/igame.h"
#include "../engine/ecs/entity_manager.h"
#include "../engine/ecs/systems/texture_render_system.h"
#include "../engine/resources/texture_manager.h"

class Renderer;

class Game : public IGame
{
  public:
    Game(Renderer* rendererPtr, TextureManager* textureManagerPtr);
    void initialize() override;
    void update(float deltaTime) override;
    void render(Renderer* renderer) override;
    void shutdown() override;
    int getPlayerEntityId() const override;
    EntityManager& getEntityManager() override;
    void setRenderer(Renderer* rendererPtr) override;

  private:
    int playerEntityId;
    EntityManager entityManager;
    Renderer* renderer;
    TextureManager* textureManager;
    std::unique_ptr<TextureRenderSystem> textureRenderSystem;
};

#endif
