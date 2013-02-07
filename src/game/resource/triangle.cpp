/*
 * game/resource/triangle.cpp
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#include <Box2D/Collision/Shapes/b2PolygonShape.h>

#include <gravity/game/math/vec2f.hpp>
#include <gravity/game/resource/triangle.hpp>

namespace Gravity {
namespace Game {

Triangle::Triangle()
{}

Triangle::Triangle(const Vec2f* vertices)
{
	b2Vec2 v[3] = { vertices[0], vertices[1], vertices[2] };
	physicsShape.Set(v, 3);
}

const b2Shape& Triangle::GetPhysicsShape() const
{
	return physicsShape;
}

IShapePrimitive* Triangle::Clone() const
{
    Triangle* triangle = new Triangle;
    *triangle = *this;
    return triangle;
}

} // namespace Game
} // namespace Gravity

