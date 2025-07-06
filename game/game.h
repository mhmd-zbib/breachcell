#ifndef GAME_H
#define GAME_H

#include "../engine/core/igame.h"
class Renderer;

class Game : public IGame
{
  public:
    Game();
    void initialize() override;
    void update(float deltaTime) override;
    void render(Renderer* renderer) override;
    void shutdown() override;
};

#endif