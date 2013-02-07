/*
 * client/renderer.hpp
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#ifndef GRAVITY_CLIENT_RENDERER_HPP
#define GRAVITY_CLIENT_RENDERER_HPP

#include <gravity/game/world.hpp>

namespace Gravity {
namespace Client {

void DrawWorld( sf::RenderWindow& renderTarget
              , const Game::World& world
              , float interpolation
              );

} // namespace Client
} // namespace Gravity

#endif /* GRAVITY_CLIENT_RENDERER_HPP */
