/*
 * game/resource/triangle.hpp
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#ifndef GRAVITY_GAME_RESOURCE_TRIANGLE_HPP
#define GRAVITY_GAME_RESOURCE_TRIANGLE_HPP

#include <Box2D/Collision/Shapes/b2PolygonShape.h>

#include <gravity/game/math/vec2f.hpp>
#include <gravity/game/resource/ishape_primitive.hpp>

namespace Gravity {
namespace Game {

class Triangle : public IShapePrimitive {
private:
    b2PolygonShape physicsShape;
    Triangle();
public:
    explicit Triangle(const Vec2f vertices[3]);
    virtual const b2Shape& GetPhysicsShape() const;
    virtual IShapePrimitive* Clone() const;
}; 

} // namespace Game
} // namespace Gravity

#endif /* GRAVITY_GAME_RESOURCE_TRIANGLE_HPP */
