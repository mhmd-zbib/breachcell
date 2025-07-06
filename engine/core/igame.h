#ifndef IGAME_H
#define IGAME_H

class Renderer;

class IGame
{
  public:
    virtual void initialize() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(Renderer* renderer) = 0;
    virtual void shutdown() = 0;
    virtual ~IGame() = default;
};

#endif
