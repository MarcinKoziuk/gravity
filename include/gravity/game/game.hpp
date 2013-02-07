/*
 * game/game.hpp
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#ifndef GRAVITY_GAME_GAME_HPP
#define GRAVITY_GAME_GAME_HPP

#include <gravity/game/world.hpp>

namespace Gravity {
namespace Game {

class Game {
private:
    World world;
    Shape* shape;
public:
    Game();
    void Start();
    void Step();
    void Stop();
    World& GetWorld();
};

} // namespace Game
} // namespace Gravity

#endif /* GRAVITY_GAME_GAME_HPP */
