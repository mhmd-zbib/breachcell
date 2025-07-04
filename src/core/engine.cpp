#include "core/engine.h"
#include "input/input_handler.h"
#include "render/renderer.h"
#include "ecs/systems/movement_system.h"
#include "ecs/systems/aiming_system.h"
#include "ecs/systems/shooting_system.h"
#include "ecs/systems/input_system.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include "render/core_render_system.h"
#include "render/texture_manager.h"
#include "factories/player_factory.h"
#include "factories/enemy_factory.h"
#include "factories/wall_factory.h"
#include "ecs/systems/collision_system.h"
#include "ecs/systems/health_system.h"
#include "core/camera_service.h"
#include <stdexcept>
#include <iostream>

Engine &Engine::getInstance()
{
  static Engine instance;
  return instance;
}

Engine::Engine() : running(false), inputHandler(nullptr), renderer(nullptr), window(nullptr) {}

bool Engine::init(const char *windowTitle, int windowWidth, int windowHeight)
{
  inputHandler = &InputHandler::getInstance();
  renderer = &Renderer::getInstance();
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    throw std::runtime_error("SDL initialization failed");
  window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
  if (!window)
    throw std::runtime_error("Window creation failed");
  if (!renderer->init(window))
    throw std::runtime_error("Renderer initialization failed");
  TextureManager::getInstance().loadTexture(1, "assets/player.png", renderer->getSDLRenderer());
  TextureManager::getInstance().loadTexture(2, "assets/enemy.png", renderer->getSDLRenderer());
  createEntities();
  running = true;
  return true;
}

void Engine::run()
{
  while (running)
  {
    handleInput();
    update();
    render();
    SDL_Delay(16);
  }
}

void Engine::handleInput()
{
  inputHandler->handleInput(running);
}

void Engine::update()
{
  EntityManager &entityManager = EntityManager::getInstance();
  TransformComponent *playerTransform = entityManager.getTransformComponent(playerEntityId);
  if (!playerTransform)
    throw std::runtime_error("Player transform not found");

  Uint32 currentTicks = SDL_GetTicks();
  static Uint32 lastTicks = currentTicks;
  float deltaTime = (currentTicks - lastTicks) / 1000.0f;
  lastTicks = currentTicks;

  MovementSystem::getInstance().update(deltaTime, playerEntityId);

  CameraService::getInstance().updateCameraPosition(static_cast<int>(playerTransform->positionX), static_cast<int>(playerTransform->positionY), 800, 600);

  InputSystem::getInstance().update();
  AimingSystem::getInstance().update(playerEntityId);
  ShootingSystem::getInstance().update(playerEntityId);
  CollisionSystem::getInstance().update();
  HealthSystem::getInstance().update();
}

void Engine::render()
{
  renderer->clear();
  CoreRenderSystem::getInstance().setRenderer(renderer->getSDLRenderer());
  CoreRenderSystem::getInstance().renderAll();
  renderer->present();
}

void Engine::clean()
{
  if (window)
  {
    SDL_DestroyWindow(window);
    window = nullptr;
  }
  SDL_Quit();
  running = false;
}

void Engine::createEntities()
{
  std::uint32_t playerEntityId = PlayerFactory::getInstance().createPlayer(400.0f, 300.0f, 0.0f, 1.0f, 1, 0);
  setPlayerEntityId(playerEntityId);
  EnemyFactory::getInstance().createEnemy(200.0f, 200.0f, 0.0f, 1.0f, 2, 1);
  WallFactory::getInstance().createWall(100.0f, 100.0f, 32.0f, 32.0f, 2);
}

void Engine::setPlayerEntityId(std::uint32_t id)
{
  std::printf("Engine::setPlayerEntityId called with id: %u\n", id);
  playerEntityId = id;
  CameraService::getInstance().setTargetEntityId(id);
}

std::uint32_t Engine::getPlayerEntityId() const
{
  return playerEntityId;
}
