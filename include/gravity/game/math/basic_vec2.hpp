/*
 * game/math/basic_vec2.hpp
 *
 * Template for the 2d vector class (simply consisting of an x and y value,
 * not to be confused with std::vector).
 *
 * Additional functions that operate on instances of this template can be
 * found in game/math.hpp.
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#ifndef GRAVITY_GAME_BASIC_VEC2_HPP
#define GRAVITY_GAME_BASIC_VEC2_HPP

#include <cmath>
#include <ostream>

/*
 * With this, we switch out certain unnecessary convenience constructors to
 * safely convert 2d vectors from other libraries. Having them on-board all
 * the time might cause longer compile times, but the main reason is that it
 * adds additional dependencies to server module (not desirable).
 *
 * Note that the resulting BasicVec2 classes might technically not be 100%
 * compatible according to the C++ standard, but practically this is not an
 * issue because no additional ctors and non-virtual members functions are
 * stored inside the object(s). So we can safely pass them around.
 */

#ifdef GRAVITY_GAME
#   include <Box2D/Box2D.h>
#endif

#ifdef GRAVITY_CLIENT
#   include <SFML/System/Vector2.hpp>
#endif

namespace Gravity {
namespace Game {

template<class T>
class BasicVec2 {
public:
	T x, y;

	BasicVec2() : x(0) , y(0)
	{}

	BasicVec2(T x, T y) : x(x), y(y)
	{}

	template<class Y>
	BasicVec2(const BasicVec2<Y>& v) : x(v.x), y(v.y)
	{}

//	explicit BasicVec2(const T* ptr)
//	{
//		assert(ptr != nullptr);
//		x = ptr[0], y = ptr[1];
//	}

#ifdef GRAVITY_GAME
	BasicVec2(const b2Vec2& v) : x(T(v.x)), y(T(v.y))
	{}
#endif

#ifdef GRAVITY_CLIENT
	BasicVec2(const sf::Vector2<T>& v) : x(v.x), y(v.y)
	{}
#endif

#ifdef GRAVITY_GAME
	operator b2Vec2() const
	{ return b2Vec2(float32(x), float32(y)); }
#endif

#ifdef GRAVITY_CLIENT
	operator sf::Vector2<T>() const
	{ return sf::Vector2<T>(x, y); }
#endif

	operator const T*() const
	{ return reinterpret_cast<const T*>(&x); }

	operator T*() const
	{ return reinterpret_cast<T*>(&x); }

	BasicVec2 operator-() const
	{ return BasicVec2(-x, -y); }

	T Length() const
	{ return T(std::sqrt(x * x + y * y)); }

	T LengthSquared() const
	{ return x * x + y * y; }

	T ToAngle() const
	{ return T(std::atan2(x, y)); }

	BasicVec2 Normalized() const
	{ return *this / Length(); }

	BasicVec2 Rotate(T angle) const
	{
		const T si = std::sin(angle);
		const T co = std::cos(angle);
		return BasicVec2(co * x - si * y, si * x + co * y);
	}
};

template<class T>
int	operator==(const BasicVec2<T>& a, const BasicVec2<T>& b)
{ return a.x == b.x && a.y == b.y; }

template<class T>
int	operator!=(const BasicVec2<T>& a, const BasicVec2<T>& b)
{ return a.x != b.x || a.y != b.y; }

template<class T>
BasicVec2<T> operator+(const BasicVec2<T>& a, const BasicVec2<T>& b)
{ return BasicVec2<T>(a.x + b.x, a.y + b.y); }

template<class T>
const BasicVec2<T>& operator+=(const BasicVec2<T>& a, const BasicVec2<T>& b)
{ a.x += b.x; a.y += b.y; return a; }

template<class T>
BasicVec2<T>& operator+=(BasicVec2<T>& a, BasicVec2<T>& b)
{ a.x += b.x; a.y += b.y; return a; }

template<class T>
BasicVec2<T> operator-(const BasicVec2<T>& a, const BasicVec2<T>& b)
{ return BasicVec2<T>(a.x - b.x, a.y - b.y); }

template<class T>
BasicVec2<T>& operator-=(BasicVec2<T>& a, const BasicVec2<T>& b)
{ a.x -= b.x; a.y -= b.y; return a; }

template<class T>
BasicVec2<T> operator*(const BasicVec2<T>& a, T k)
{ return BasicVec2<T>(a.x * k, a.y * k); }

template<class T>
BasicVec2<T> operator*(T k, const BasicVec2<T>& a)
{ return BasicVec2<T>(a.x * k, a.y * k); }

template<class T>
BasicVec2<T>& operator*=(BasicVec2<T>& a, T k)
{ a.x *= k; a.y *= k; return a; }

template<class T>
BasicVec2<T> operator*(const BasicVec2<T>& a, const BasicVec2<T>& b)
{ return BasicVec2<T>(a.x * b.x, a.y * b.y); }

template<class T>
BasicVec2<T>& operator*=(BasicVec2<T>& a, const BasicVec2<T>& b)
{ a.x *= b.x; a.y *= b.y; return a; }

template<class T>
BasicVec2<T> operator/(const BasicVec2<T>& a, T k)
{ return BasicVec2<T>(a.x / k, a.y / k); }

template<class T>
BasicVec2<T> operator/(T k, const BasicVec2<T>& a)
{ return BasicVec2<T>(k / a.x, k / a.y); }

template<class T>
BasicVec2<T>& operator/=(BasicVec2<T>& a, T k)
{ a.x /= k; a.y /= k; return a; }

template<class T>
BasicVec2<T> operator/(const BasicVec2<T>& a, const BasicVec2<T>& b)
{ return BasicVec2<T>(a.x / b.x, a.y / b.y); }

template<class T>
BasicVec2<T>& operator/=(BasicVec2<T>& a, const BasicVec2<T>& b)
{ a.x /= b.x; a.x /= b.y; return a; }

template<class T>
std::ostream& operator<<(std::ostream& os, const BasicVec2<T>& vec)
{
    os << '(' << vec.x << ", " << vec.y << ')';
    return os;
}

} // namespace Game
} // namespace Gravity


#endif /* GRAVITY_GAME_BASIC_VEC2_HPP */
