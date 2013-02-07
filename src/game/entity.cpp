/*
 * game/entity.cpp
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#include <Box2D/Box2D.h>

#include <gravity/game/logging.hpp>
#include <gravity/game/world.hpp>
#include <gravity/game/entity.hpp>


namespace Gravity {
namespace Game {

Entity::Entity(World& world, const Shape& shape, const Vec2f& pos)
    : body(*world.CreatePhysicsBody(pos, shape))
    , shape(shape)
{
    //GRAVITY_LOG(debug, "New entity created at address 0x%1%.") % this;
}

} // namespace Game
} // namespace Gravity

