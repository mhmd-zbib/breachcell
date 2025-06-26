#include <SDL2/SDL.h>
#include <iostream>
#include "core/engine.h"
#include "input/input_handler.h"
#include "render/renderer.h"
#include "ecs/systems/render_system.h"
#include "ecs/systems/movement_system.h"
#include "ecs/systems/aiming_system.h"
#include "ecs/components.h"
#include "ecs/entity_manager.h"
#include "factories/player_factory.h"

int main()
{
  InputHandler &inputHandler = InputHandler::getInstance();
  Renderer &renderer = Renderer::getInstance();
  Engine &engine = Engine::getInstance(inputHandler, renderer);
  RenderSystem &renderSystem = RenderSystem::getInstance();
  if (!engine.init("BreachCell 2D Game", 800, 600))
    return 1;
  renderSystem.loadTextures();
  std::uint32_t playerEntityId = PlayerFactory::getInstance().createPlayer(400.0f, 300.0f, 0.0f, 1.0f, 1, 0);
  engine.setPlayerEntityId(playerEntityId);
  while (engine.isRunning())
  {
    engine.handleInput();
    engine.update();
    engine.render();
    SDL_Delay(16);
  }
  engine.clean();
  return 0;
}
