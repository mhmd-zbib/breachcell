#include <SDL2/SDL.h>
#include <iostream>
#include "core/engine.h"
#include "input/input_handler.h"
#include "render/renderer.h"
#include "ecs/systems/render_system.h"
#include "ecs/systems/movement_system.h"
#include "ecs/components.h"
#include "ecs/entity_manager.h"
#include "factories/player_factory.h"

int main()
{
  InputHandler &inputHandler = InputHandler::getInstance();
  Renderer &renderer = Renderer::getInstance();
  Engine &engine = Engine::getInstance(inputHandler, renderer);
  RenderSystem &renderSystem = RenderSystem::getInstance();
  MovementSystem &movementSystem = MovementSystem::getInstance();
  if (!engine.init("BreachCell 2D Game", 800, 600))
    return 1;

  renderSystem.loadTextures();

  std::uint32_t playerEntityId = PlayerFactory::getInstance().createPlayer(400.0f, 300.0f, 0.0f, 1.0f, 1, 0);
  movementSystem.setPlayerEntityId(playerEntityId);

  Uint32 lastTicks = SDL_GetTicks();
  while (engine.isRunning())
  {
    engine.handleInput();
    Uint32 currentTicks = SDL_GetTicks();
    float deltaTime = (currentTicks - lastTicks) / 1000.0f;
    lastTicks = currentTicks;
    movementSystem.update(deltaTime);
    engine.update();
    renderer.clear();
    renderSystem.renderAll();
    renderer.present();
    SDL_Delay(16);
  }
  engine.clean();
  return 0;
}
