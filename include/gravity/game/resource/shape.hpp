/*
 * game/resource/shape.hpp
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#ifndef GRAVITY_GAME_RESOURCE_SHAPE_HPP
#define GRAVITY_GAME_RESOURCE_SHAPE_HPP

#include <boost/utility.hpp>
#include <boost/ptr_container/ptr_deque.hpp>

#include <gravity/game/resource/ishape_primitive.hpp>

namespace Gravity {
namespace Game {

class Shape : boost::noncopyable {
private:
    boost::ptr_deque<IShapePrimitive> shapePrimitives;
public:
    Shape();
    void AddPrimitive(const IShapePrimitive& shapePrimitive);

    const boost::ptr_deque<IShapePrimitive>& GetAllPrimitives() const;
    static Shape* CreateShipShape();
    static Shape* CreatePlanetShape();
    static Shape* CreateBombShape();
};

} // namespace Game
} // namespace Gravity

#endif /* GRAVITY_GAME_RESOURCE_SHAPE_HPP */
