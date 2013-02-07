/*
 * game/resource/ishape_primitive.hpp
 *
 * Defines an interface for a shape primitive, such as a Triangle or Circle.
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#ifndef GRAVITY_GAME_RESOURCE_ISHAPE_PRIMITIVE_HPP
#define GRAVITY_GAME_RESOURCE_ISHAPE_PRIMITIVE_HPP

#include <boost/utility.hpp>

#include <Box2D/Collision/Shapes/b2Shape.h>

namespace Gravity {
namespace Game {

class IShapePrimitive {
public:
    virtual ~IShapePrimitive() {}
	virtual const b2Shape& GetPhysicsShape() const = 0;
    virtual IShapePrimitive* Clone() const = 0;
};

inline IShapePrimitive* new_clone(const IShapePrimitive& o)
{ return o.Clone(); }

} // namespace Game
} // namespace Gravity

#endif /* GRAVITY_GAME_RESOURCE_ISHAPE_PRIMITIVE_HPP */
