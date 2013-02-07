/*
 * game/world.cpp
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#include <Box2D/Box2D.h>

#include <boost/foreach.hpp>

#include <gravity/game/math/math.hpp>
#include <gravity/game/logging.hpp>
#include <gravity/game/entity.hpp>
#include <gravity/game/world.hpp>

namespace Gravity {
namespace Game {

World::World()
    : physicsWorld(Vec2f(0,0))
{}

void World::AddEntity(Entity& entity)
{
    //GRAVITY_LOG(debug, "Added entity 0x%1% to world.") % &entity;
    entities.push_back(&entity);
}

const std::deque<Entity*>& World::GetEntities() const
{
    return entities;
}

void World::Step()
{
    physicsWorld.Step(1.f/60.f, 6, 3);
    ApplyGravity();
}

void World::ApplyGravity()
{
	typedef std::deque<Entity*>::const_iterator DequeConstIter;
	typedef std::vector<Entity*>::iterator VecIter;

	std::vector<Entity*> astroEnts;
	std::vector<Entity*> normalEnts;

    for (DequeConstIter p = entities.begin(); p != entities.end(); p++) {
        if ((*p)->GetMass() > 300)
			astroEnts.push_back(*p);
        else
			normalEnts.push_back(*p);

	}
    //normalEnts.push_back(entities[0]);
    //astroEnts.push_back(entities[1]);


	for (VecIter p = normalEnts.begin(); p != normalEnts.end(); p++) {
		for (VecIter q = astroEnts.begin(); q != astroEnts.end(); q++) {
			Entity& normal = **p;
			Entity& astro = **q;
            const Vec2f normalPos = normal.GetPos();
            const Vec2f astroPos = astro.GetPos();
            const float dist = Distance(astroPos, normalPos);
            const float gravConstant = 200.f;
            Vec2f gravVec = (normalPos - astroPos).Normalized();

            gravVec *= -(gravConstant * normal.GetMass())/(dist * dist);
            normal.ApplyForce(gravVec);
		}
	}
}

b2Body* World::CreatePhysicsBody(const Vec2f& position, const Shape& shape)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = position;
    b2Body* body = physicsWorld.CreateBody(&bodyDef);

    BOOST_FOREACH(const IShapePrimitive& primitive, shape.GetAllPrimitives()) {
        body->CreateFixture(&primitive.GetPhysicsShape(), 1.f);
    }

    return body;
}

} // namespace Game
} // namespace Gravity

