/*
 * client/render/renderer.cpp
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#include <boost/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>

#include <SFML/Graphics.hpp>

#include <gravity/game/math/math.hpp>
#include <gravity/game/resource/shape.hpp>
#include <gravity/game/entity.hpp>
#include <gravity/game/world.hpp>
#include <gravity/game/entity.hpp>

#include <gravity/client/options.hpp>
#include <gravity/client/render/renderer.hpp>

using namespace Gravity;
using namespace Gravity::Client;
using namespace Gravity::Game;

namespace {

void DrawEntity(sf::RenderWindow& renderTarget, const Entity& entity)
{
    const Shape& shape = entity.GetShape();
    const float scale = Options::GetInstance().renderscale;

    BOOST_FOREACH(const IShapePrimitive& primitive, shape.GetAllPrimitives()) {
        const b2Shape& shape = primitive.GetPhysicsShape();
        if (shape.GetType() == b2Shape::e_polygon) {
            const b2PolygonShape& polygon = dynamic_cast<const b2PolygonShape&>(shape);
            sf::ConvexShape convex(polygon.GetVertexCount());
            for (int i = 0; i < polygon.GetVertexCount(); i++)
                convex.setPoint(i, Vec2f(polygon.GetVertex(i)) * scale);
            convex.setFillColor(sf::Color(0, 20, 60));
		
            convex.setOutlineColor(sf::Color::Cyan);
            convex.setOutlineThickness(.8);
            convex.setRotation(RadToDeg(entity.GetAngle()));
            convex.setPosition(entity.GetPos() * scale);
            
            renderTarget.draw(convex);
        } else if (shape.GetType() == b2Shape::e_circle) {
            const b2CircleShape& pcircle = dynamic_cast<const b2CircleShape&>(shape);
            const float radius = pcircle.m_radius * scale;
            sf::CircleShape scircle(pcircle.m_radius * scale, 70);
            scircle.setOrigin(radius, radius);
            scircle.setFillColor(sf::Color(0, 20, 60));
            scircle.setOutlineColor(sf::Color::Cyan);
            scircle.setOutlineThickness(1);
            scircle.setRotation(RadToDeg(entity.GetAngle()));
            scircle.setPosition(entity.GetPos() * scale);

            renderTarget.draw(scircle);
        }
    }
}

} // namespace

namespace Gravity {
namespace Client {

void DrawWorld( sf::RenderWindow& renderTarget
              , const Game::World& world
              , float interpolation
              )
{
    BOOST_ASSERT(interpolation >= 0.f && interpolation <= 1.f);

    BOOST_FOREACH(const Entity* entity, world.GetEntities()) {
        DrawEntity(renderTarget, *entity);
    }

    return;
}

} // namespace Client
} // namespace Gravity
