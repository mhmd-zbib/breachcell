#include "game.h"
#include "../engine/graphics/circle_shape.h"
#include "../engine/graphics/rectangle_shape.h"
#include "../engine/graphics/renderer.h"
#include "../engine/graphics/shape_renderer.h"

Game::Game() {}

void Game::initialize() {}

void Game::update(float deltaTime) {}

void Game::render(Renderer* renderer)
{
    RectangleShape rectangle(100, 100, 200, 100, 255, 0, 0, 255);
    CircleShape circle(400, 300, 50, 0, 0, 255, 255);
    renderer->getShapeRenderer()->drawShape(&rectangle, ShapeStyle::Filled);
    renderer->getShapeRenderer()->drawShape(&circle, ShapeStyle::Outline);
}

void Game::shutdown() {}
