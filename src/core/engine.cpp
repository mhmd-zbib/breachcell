#include "core/engine.h"
#include "render/renderer.h"
#include "input/input_handler.h"
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

void Engine::update()
{
}

void Engine::render()
{
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
