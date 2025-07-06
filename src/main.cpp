#include "core/camera_service.h"
#include "core/engine.h"
#include "core/game_builder.h"
#include "core/game_facade.h"
#include "core/platform_abstraction.h"
#include "ecs/entity_manager.h"
#include "ecs/systems/aiming_system.h"
#include "ecs/systems/health_system.h"
#include "ecs/systems/input_system.h"
#include "ecs/systems/movement_system.h"
#include "ecs/systems/shooting_system.h"
#include "factories/enemy_factory.h"
#include "factories/player_factory.h"
#include "factories/projectile_factory.h"
#include "factories/wall_factory.h"
#include "input/input_handler.h"
#include "render/aiming_renderer.h"
#include "render/core_render_system.h"
#include "render/entity_renderer.h"
#include "render/projectile_renderer.h"
#include "render/renderer.h"
#include "render/texture_manager.h"
#include "render/wall_renderer.h"

int main() {
  auto game = GameBuilder::buildGame("BreachCell", 800, 600);
  return game.start();
}
