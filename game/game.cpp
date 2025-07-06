#include "game.h"
#include "entities/BoxFactory.h"
#include "entities/PlayerFactory.h"

Game::Game() : playerEntityId(1) {}

void Game::initialize()
{
    playerEntityId = PlayerFactory::createPlayerEntity(entityManager, 400.0f, 300.0f, 200.0f);
    BoxFactory::createBoxEntity(entityManager, 100.0f, 100.0f, 60.0f, 60.0f, 255, 0, 0, 255);
    BoxFactory::createBoxEntity(entityManager, -200.0f, -100.0f, 60.0f, 60.0f, 255, 0, 0, 255);
}

int Game::getPlayerEntityId() const
{
    return playerEntityId;
}

void Game::update(float deltaTime) {}

void Game::render(Renderer* renderer) {}

void Game::shutdown() {}

EntityManager& Game::getEntityManager()
{
    return entityManager;
}
