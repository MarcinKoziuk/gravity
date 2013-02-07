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
                convex.SetPoint(i, Vec2f(polygon.GetVertex(i)) * scale);
            convex.SetFillColor(sf::Color(0, 20, 60));
		
            convex.SetOutlineColor(sf::Color::Cyan);
            convex.SetOutlineThickness(.8);
            convex.SetRotation(RadToDeg(entity.GetAngle()));
            convex.SetPosition(entity.GetPos() * scale);
            
            renderTarget.Draw(convex);
        } else if (shape.GetType() == b2Shape::e_circle) {
            const b2CircleShape& pcircle = dynamic_cast<const b2CircleShape&>(shape);
            const float radius = pcircle.m_radius * scale;
            sf::CircleShape scircle(pcircle.m_radius * scale, 70);
            scircle.SetOrigin(radius, radius);
            scircle.SetFillColor(sf::Color(0, 20, 60));
            scircle.SetOutlineColor(sf::Color::Cyan);
            scircle.SetOutlineThickness(1);
            scircle.SetRotation(RadToDeg(entity.GetAngle()));
            scircle.SetPosition(entity.GetPos() * scale);

            renderTarget.Draw(scircle);
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
