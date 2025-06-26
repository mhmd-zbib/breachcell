#include "core/engine.h"
#include "render/renderer.h"
#include "input/input_handler.h"
#include "ecs/systems/movement_system.h"
#include "ecs/systems/aiming_system.h"
#include "ecs/systems/render_system.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include <stdexcept>
#include <iostream>

Engine::Engine(InputHandler &inputHandler, Renderer &renderer)
    : inputHandlerReference(inputHandler), rendererReference(renderer), window(nullptr), running(false) {}

Engine &Engine::getInstance(InputHandler &inputHandler, Renderer &renderer)
{
  static Engine instance(inputHandler, renderer);
  return instance;
}

bool Engine::init(const char *windowTitle, int windowWidth, int windowHeight)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    throw std::runtime_error("SDL initialization failed");
  window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
  std::cout << "SDL_CreateWindow returned: " << window << std::endl;
  if (!window)
  {
    std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
    throw std::runtime_error("Window creation failed");
  }
  if (!rendererReference.init(window))
  {
    std::cerr << "Renderer initialization failed: " << SDL_GetError() << std::endl;
    throw std::runtime_error("Renderer initialization failed");
  }
  std::cout << "Renderer pointer: " << rendererReference.getSDLRenderer() << std::endl;
  running = true;
  InputSystem::getInstance().setRunning(running);
  return true;
}

bool Engine::isRunning() const
{
  return running;
}

void Engine::handleInput()
{
  inputHandlerReference.handleInput(running);
}

void Engine::setPlayerEntityId(std::uint32_t id)
{
  playerEntityId = id;
  MovementSystem::getInstance().setPlayerEntityId(id);
  AimingSystem::getInstance().setPlayerEntityId(id);
}

void Engine::update()
{
  InputSystem::getInstance().update();
  AimingSystem::getInstance().update();
  Uint32 currentTicks = SDL_GetTicks();
  static Uint32 lastTicks = currentTicks;
  float deltaTime = (currentTicks - lastTicks) / 1000.0f;
  lastTicks = currentTicks;
  MovementSystem::getInstance().update(deltaTime);
}

void Engine::render()
{
  rendererReference.clear();
  RenderSystem::getInstance().renderAll();
  RenderSystem::getInstance().renderAimLine();
  rendererReference.present();
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
