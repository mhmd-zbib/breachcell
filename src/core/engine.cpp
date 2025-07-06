#include "core/engine.h"
#include <SDL2/SDL.h>
#include <stdexcept>

Engine::Engine(EngineConfig config) :
    running(false),
    inputHandler(std::move(config.inputHandler)),
    renderer(std::move(config.renderer)),
    entityManager(std::move(config.entityManager)),
    textureManager(std::move(config.textureManager)),
    cameraService(std::move(config.cameraService)),
    platformAbstraction(std::move(config.platformAbstraction)),
    coreRenderSystem(std::move(config.coreRenderSystem)),
    movementSystem(std::move(config.movementSystem)),
    inputSystem(std::move(config.inputSystem)),
    aimingSystem(std::move(config.aimingSystem)),
    shootingSystem(std::move(config.shootingSystem)),
    healthSystem(std::move(config.healthSystem)),
    window(nullptr),
    playerEntityId(0) {
}

bool Engine::initialize(const char* windowTitle, int windowWidth, int windowHeight) {
  platformAbstraction->initializeSDL();
  platformAbstraction->createWindow(windowTitle, windowWidth, windowHeight);
  window = platformAbstraction->getWindow();
  if (!renderer->init(window))
    throw std::runtime_error("Renderer initialization failed");
  textureManager->loadTextures(renderer->getSDLRenderer());
  std::uint32_t playerEntityId = entityManager->createEntities();
  setPlayerEntityId(playerEntityId);
  running = true;
  return true;
}

void Engine::handleInput() {
  inputHandler->handleInput(running);
}

void Engine::update() {
  TransformComponent* playerTransform = entityManager->getTransformComponent(playerEntityId);
  if (!playerTransform) {
    throw std::runtime_error("Player transform not found");
  }
  Uint32        currentTicks = SDL_GetTicks();
  static Uint32 lastTicks    = currentTicks;
  float         deltaTime    = (currentTicks - lastTicks) / 1000.0f;
  lastTicks                  = currentTicks;
  int windowWidth            = 0;
  int windowHeight           = 0;
  platformAbstraction->getWindowSize(windowWidth, windowHeight);
  movementSystem->update(deltaTime, playerEntityId);
  cameraService->updateCameraPosition(static_cast<int>(playerTransform->positionX),
                                      static_cast<int>(playerTransform->positionY), windowWidth,
                                      windowHeight);
  inputSystem->update();
  aimingSystem->update(playerEntityId);
  shootingSystem->update(playerEntityId);
  healthSystem->update();
}

void Engine::render() {
  renderer->clear();
  coreRenderSystem->setRenderer(renderer->getSDLRenderer());
  coreRenderSystem->renderAll(playerEntityId, entityManager.get(), cameraService.get());
  renderer->present();
}

void Engine::cleanup() {
  platformAbstraction->destroyWindow();
  platformAbstraction->shutdownSDL();
}

void Engine::createEntities() {
}

void Engine::setPlayerEntityId(std::uint32_t id) {
  playerEntityId = id;
  cameraService->setTargetEntityId(id);
}

std::uint32_t Engine::getPlayerEntityId() const {
  return playerEntityId;
}
