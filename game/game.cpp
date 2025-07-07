#include "game.h"
#include "../engine/graphics/renderer.h"
#include "../engine/resources/texture_manager.h"
#include "entities/BoxFactory.h"
#include "entities/PlayerFactory.h"
#include <stdexcept>

Game::Game(Renderer* rendererPtr, TextureManager* textureManagerPtr)
    : playerEntityId(1), renderer(rendererPtr), textureManager(textureManagerPtr)
{
    if (!renderer)
        throw std::invalid_argument("Renderer pointer is null");
    if (!textureManager)
        throw std::invalid_argument("TextureManager pointer is null");
}

void Game::initialize()
{
    int playerTextureId = textureManager->loadTexture("player", "assets/player.png");
    playerEntityId = PlayerFactory::createPlayerEntity(entityManager, 400.0f, 300.0f, 200.0f, playerTextureId);
    BoxFactory::createBoxEntity(entityManager, 100.0f, 100.0f, 60.0f, 60.0f, 255, 0, 0, 255);
    BoxFactory::createBoxEntity(entityManager, -200.0f, -100.0f, 60.0f, 60.0f, 255, 0, 0, 255);
    textureRenderSystem = std::make_unique<TextureRenderSystem>(textureManager);
}

int Game::getPlayerEntityId() const
{
    return playerEntityId;
}

void Game::update(float deltaTime) {}

void Game::render(Renderer* renderer)
{
    if (textureRenderSystem)
        textureRenderSystem->render(entityManager, renderer);
}

void Game::shutdown() {}

EntityManager& Game::getEntityManager()
{
    return entityManager;
}

void Game::setRenderer(Renderer* rendererPtr)
{
    renderer = rendererPtr;
}
