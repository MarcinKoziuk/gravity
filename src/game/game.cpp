/*
 * game/game.cpp
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#include <gravity/game/logging.hpp>
#include <gravity/game/entity.hpp>
#include <gravity/game/game.hpp>

namespace Gravity {
namespace Game {

Game::Game()
    : shape(Shape::CreateShipShape())
{}

void Game::Start()
{
    Entity* entity = new Entity(world, *shape, Vec2f(1, 1));
    Shape* planetShape = Shape::CreatePlanetShape();
    Entity* entity2 = new Entity(world, *planetShape, Vec2f(23, 23));
    entity2->SetMass(500);
   
    world.AddEntity(*entity);
    world.AddEntity(*entity2);
}

void Game::Step()
{
    world.Step();
}

void Game::Stop()
{
}

World& Game::GetWorld()
{
    return world;
}

} // namespace Game
} // namespace Gravity

