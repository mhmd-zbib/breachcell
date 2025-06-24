#include <SDL2/SDL.h>
#include <iostream>
#include "core/engine.h"
#include "input/input_handler.h"
#include "render/renderer.h"
#include "ecs/systems/render_system.h"
#include "ecs/components.h"
#include "ecs/entity_manager.h"

int main()
{
  InputHandler &inputHandler = InputHandler::getInstance();
  Renderer &renderer = Renderer::getInstance();
  Engine &engine = Engine::getInstance(inputHandler, renderer);
  RenderSystem &renderSystem = RenderSystem::getInstance();
  if (!engine.init("BreachCell 2D Game", 800, 600))
    return 1;

  renderSystem.loadTextures();

  EntityManager &entityManager = EntityManager::getInstance();
  std::uint32_t playerEntityId = entityManager.createEntity();
  TransformComponent playerTransform{400.0f, 300.0f, 0.0f, 1.0f};
  VelocityComponent playerVelocity{0.0f, 0.0f};
  SpriteComponent playerSprite{1, 0};
  InputComponent playerInput{false, false, false, false};
  entityManager.addTransformComponent(playerEntityId, playerTransform);
  entityManager.addVelocityComponent(playerEntityId, playerVelocity);
  entityManager.addSpriteComponent(playerEntityId, playerSprite);
  entityManager.addInputComponent(playerEntityId, playerInput);

  while (engine.isRunning())
  {
    engine.handleInput();
    engine.update();
    renderer.clear();
    renderSystem.renderAll();
    renderer.present();
    SDL_Delay(16);
  }
  engine.clean();
  return 0;
}
