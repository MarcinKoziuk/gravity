/*
 * game/world.hpp
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#ifndef GRAVITY_GAME_WORLD_HPP
#define GRAVITY_GAME_WORLD_HPP

#include <deque>

#include <boost/utility.hpp>

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>

#include <gravity/game/math/vec2f.hpp>
#include <gravity/game/resource/shape.hpp>
#include <gravity/game/entity_fwd.hpp>

namespace Gravity {
namespace Game {

class World : private boost::noncopyable {
private:
    std::deque<Entity*> entities;
    b2World physicsWorld;

    void ApplyGravity();
public:
    World();
    void AddEntity(Entity& entity);
    const std::deque<Entity*>& GetEntities() const;
    void Step();
    b2Body* CreatePhysicsBody(const Vec2f& position, const Shape& shape);
};

} // namespace Game
} // namespace Gravity

#endif /* GRAVITY_GAME_WORLD_HPP */
