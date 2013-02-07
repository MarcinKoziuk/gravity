/*
 * client/bounding_camera.cpp
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#include <gravity/client/bounding_camera.hpp>

using namespace Gravity::Game;

namespace Gravity {
namespace Client {

BoundingCamera::BoundingCamera(const Vec2f& size, const Vec2f& entityPos)
	: size(size)
	, entityPos(entityPos)
	, cameraPos(entityPos)
{}

void BoundingCamera::Update(const Vec2f& entityPos)
{
	const float maxHorizOffs = size.x / 2;
	const float maxVerticalOffs = size.y / 2;
	const float horizOffs = cameraPos.x - entityPos.x;
	const float verticalOffs = cameraPos.y - entityPos.y;

	if (horizOffs > maxHorizOffs)
		cameraPos.x += (maxHorizOffs - horizOffs);
	if (horizOffs < -maxHorizOffs)
		cameraPos.x -= (maxHorizOffs + horizOffs);
	if (verticalOffs > maxVerticalOffs)
		cameraPos.y += (maxVerticalOffs - verticalOffs);
	if (verticalOffs < -maxVerticalOffs)
		cameraPos.y -= (maxVerticalOffs + verticalOffs);

	this->entityPos = entityPos;
}

const Vec2f& BoundingCamera::GetPos() const
{
	return cameraPos;
}

} // namespace Client
} // namespace Gravity
