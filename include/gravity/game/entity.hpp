/*
 * game/entity.hpp
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#ifndef GRAVITY_GAME_ENTITY_HPP
#define GRAVITY_GAME_ENTITY_HPP

#include <string>

#include <boost/utility.hpp>

#include <Box2D/Dynamics/b2Body.h>

#include <gravity/game/math/vec2f.hpp>
#include <gravity/game/math/math.hpp>
#include <gravity/game/world_fwd.hpp>
#include <gravity/game/resource/shape.hpp>

namespace Gravity {
namespace Game {

class Entity : private boost::noncopyable {
private:
    b2Body& body;
    const Shape& shape;
    
public:
    Entity(World& world, const Shape& shape, const Vec2f& pos = Vec2f(0, 0));

    virtual ~Entity()
    {}

    Vec2f GetPos() const
    { return Vec2f(body.GetPosition()); }

    Vec2f GetVel() const
    { return Vec2f(body.GetLinearVelocity()); }

    float GetAngVel() const // in radians/second
    { return body.GetAngularVelocity(); }

    float GetX() const
    { return body.GetPosition().x; }

    float GetY() const
    { return body.GetPosition().y; }

    float GetXSpeed() const
    { return body.GetLinearVelocity().x; }

    float GetYSpeed() const
    { return body.GetLinearVelocity().y; }

    float GetAngle() const // in radians
    { return body.GetAngle(); }

    float GetSpeed() const
    { Vec2f vel(body.GetLinearVelocity()); return vel.Length(); }

    float GetDirection() const
    { return float(RadToDeg(atan2(GetYSpeed(), GetXSpeed()))); }

    float GetMass() const
    { return body.GetMass(); }

    void SetVel(const Vec2f& v)
    { body.SetLinearVelocity(v); }

    void SetAngVel(float vel)
    { body.SetAngularVelocity(vel); }

    void SetSpeed(float speed);

    void SetMass(float mass)
    { b2MassData prev;
    body.GetMassData(&prev);
    prev.mass = mass;
    body.SetMassData(&prev);
    }

    void ApplyForce(const Vec2f& force)
    { body.ApplyForce(force, body.GetPosition()); }

    void ApplyTorque(float torque)
    { body.ApplyTorque(torque); }

    void Rotate(int direction)
    { body.ApplyTorque((direction - body.GetAngularVelocity())); }

    const Shape& GetShape() const
    { return shape; }
};

} // namespace Game
} // namespace Gravity

#endif /* GRAVITY_GAME_ENTITY_HPP */
