/*
 * game/resource/circle.cpp
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#include <Box2D/Collision/Shapes/b2CircleShape.h>

#include <gravity/game/resource/circle.hpp>

namespace Gravity {
namespace Game {

Circle::Circle()
    : physicsShape()
{}

Circle::Circle(float radius)
{
    physicsShape.m_radius = float32(radius);
}

const b2Shape& Circle::GetPhysicsShape() const
{
	return physicsShape;
}

IShapePrimitive* Circle::Clone() const
{
    Circle* circle = new Circle;
    *circle = *this;
    return circle;
}

} // namespace Game
} // namespace Gravity

