/*
 * game/resource/shape.cpp
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>

#include <boost/scoped_ptr.hpp>

#include <gravity/game/math/vec2f.hpp>

#include <gravity/game/resource/ishape_primitive.hpp>
#include <gravity/game/resource/shape.hpp>
#include <gravity/game/resource/triangle.hpp>
#include <gravity/game/resource/circle.hpp>

namespace Gravity {
namespace Game {

Shape::Shape()
{}

void Shape::AddPrimitive(const IShapePrimitive& shapePrimitive)
{
    shapePrimitives.push_back(shapePrimitive.Clone());
}

const boost::ptr_deque<IShapePrimitive>& Shape::GetAllPrimitives() const
{
    return shapePrimitives;
}

Shape* Shape::CreateShipShape()
{
    Shape* shape = new Shape;
    static Vec2f triangles[][3] = {
        { Vec2f(0.2f, 0.1f), Vec2f(0.f, 0.8f), Vec2f(0.f, 0.f) },
        { Vec2f(0.2f, 0.1f), Vec2f(0.f, 0.f), Vec2f(0.f, -0.1f)},
        { Vec2f(0.f, -0.1f), Vec2f(0.5f, -0.3f), Vec2f(0.4f, 0.3f) },
        { Vec2f(0.f, 0.f), Vec2f(0.f, 0.8f), Vec2f(-0.2f, 0.1f) },
        { Vec2f(0.f, -0.1f), Vec2f(0.f, 0.f), Vec2f(-0.2f, 0.1f) },
        { Vec2f(-0.4f, 0.3f), Vec2f(-0.5f, -0.3f), Vec2f(0.f, -0.1f) }
    };

    for (const Vec2f* triangle = triangles[0];
        triangle < triangles[sizeof(triangles)/sizeof(*triangles)];
        triangle+=3)
    {
        boost::scoped_ptr<IShapePrimitive> primitive(new Triangle(triangle));
        shape->AddPrimitive(*primitive);
    }

    return shape;
}

Shape* Shape::CreatePlanetShape()
{
    Shape* shape = new Shape;
    shape->AddPrimitive(*(new Circle(7)));
    return shape;
}

Shape* Shape::CreateBombShape()
{
    Shape* shape = new Shape;
    shape->AddPrimitive(*(new Circle(.1)));
    return shape;
}

} // namespace Game
} // namespace Gravity

