/*
 * client/bounding_camera.hpp
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#ifndef GRAVITY_CLIENT_BOUNDING_CAMERA_HPP
#define GRAVITY_CLIENT_BOUNDING_CAMERA_HPP

#include <gravity/game/math/vec2f.hpp>

namespace Gravity {
namespace Client {

class BoundingCamera {
private:
	Gravity::Game::Vec2f size;
	Gravity::Game::Vec2f entityPos;
	Gravity::Game::Vec2f cameraPos;
public:
	BoundingCamera( const Gravity::Game::Vec2f& size
                  , const Gravity::Game::Vec2f& entityPos
                  );
	void Update(const Gravity::Game::Vec2f& entityPos);
	const Gravity::Game::Vec2f& GetPos() const;
};

} // namespace Client
} // namespace Gravity

#endif /* GRAVITY_CLIENT_BOUNDING_CAMERA_HPP */
