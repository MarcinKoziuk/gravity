/*
 * game/resource/circle.hpp
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#ifndef GRAVITY_GAME_RESOURCE_CIRCLE_HPP
#define GRAVITY_GAME_RESOURCE_CIRCLE_HPP

#include <Box2D/Collision/Shapes/b2CircleShape.h>

#include <gravity/game/math/vec2f.hpp>
#include <gravity/game/resource/ishape_primitive.hpp>

namespace Gravity {
namespace Game {

class Circle : public IShapePrimitive {
private:
    b2CircleShape physicsShape;
    Circle();
public:
    explicit Circle(float radius);
    virtual const b2Shape& GetPhysicsShape() const;
    virtual IShapePrimitive* Clone() const;
}; 

} // namespace Game
} // namespace Gravity

#endif /* GRAVITY_GAME_RESOURCE_CIRCLE_HPP */
