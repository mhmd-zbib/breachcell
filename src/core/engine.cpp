#include "core/engine.h"
#include <SDL2/SDL.h>
#include <stdexcept>

Engine::Engine(InputHandler* inputHandler, Renderer* renderer, EntityManager* entityManager,
               TextureManager* textureManager, CameraService* cameraService,
               PlatformAbstraction* platformAbstraction, CoreRenderSystem* coreRenderSystem,
               MovementSystem* movementSystem, InputSystem* inputSystem, AimingSystem* aimingSystem,
               ShootingSystem* shootingSystem, HealthSystem* healthSystem)
    : running(false), inputHandler(inputHandler), renderer(renderer), entityManager(entityManager),
      textureManager(textureManager), cameraService(cameraService),
      platformAbstraction(platformAbstraction), coreRenderSystem(coreRenderSystem),
      movementSystem(movementSystem), inputSystem(inputSystem), aimingSystem(aimingSystem),
      shootingSystem(shootingSystem), healthSystem(healthSystem), window(nullptr),
      playerEntityId(0) {}

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

void Engine::run() {
  while (running) {
    handleInput();
    update();
    render();
    SDL_Delay(16);
  }
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
  coreRenderSystem->renderAll(playerEntityId, entityManager, cameraService);
  renderer->present();
}

void Engine::clean() {
  platformAbstraction->destroyWindow();
  platformAbstraction->shutdownSDL();
  running = false;
}

void Engine::createEntities() {}

void Engine::setPlayerEntityId(std::uint32_t id) {
  playerEntityId = id;
  cameraService->setTargetEntityId(id);
}

std::uint32_t Engine::getPlayerEntityId() const {
  return playerEntityId;
}
