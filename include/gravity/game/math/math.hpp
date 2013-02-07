/*
 * game/math/math.hpp
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#ifndef GRAVITY_GAME_MATH_HPP
#define GRAVITY_GAME_MATH_HPP

#include <gravity/game/math/basic_vec2.hpp>

namespace Gravity {
namespace Game {

template<class T>
T Distance(const BasicVec2<T>& a, const BasicVec2<T>& b)
{
	return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

template<class T>
T Dot(const BasicVec2<T>& a, const BasicVec2<T>& b)
{
	return a.x * b.x + a.y * b.y;
}


// From 0 to 360
template<class T>
T NormalizeAngle(T angle)
{
    return angle - (floor(angle / 360) * 360);
}

template<class T>
T RadToDeg(T radian)
{
    return radian * T(57.29577951308232);
}

template<class T>
T DegToRad(T degree)
{
    return degree * T(.0174532925199432958);
}

} // namespace Game
} // namespace Gravity

#endif /* GRAVITY_GAME_MATH_HPP */
