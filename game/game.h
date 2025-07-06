#ifndef GAME_H
#define GAME_H

#include "../engine/core/igame.h"
#include "../engine/ecs/entity_manager.h"

class Game : public IGame
{
  public:
    Game();
    void initialize() override;
    void update(float deltaTime) override;
    void render(Renderer* renderer) override;
    void shutdown() override;
    int getPlayerEntityId() const;
    EntityManager& getEntityManager();

  private:
    int playerEntityId;
    EntityManager entityManager;
};

#endif