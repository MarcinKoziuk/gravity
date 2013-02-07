/*
 * server/main.cpp
 *
 * Starts the server.
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#include <iostream>

#include <gravity/game/math/basic_vec2.hpp>
#include <gravity/game/math/math.hpp>
#include <gravity/game/logging.hpp>

using namespace Gravity;

int main(int argc, char *argv[])
{
    Game::InitializeLogging();
    GRAVITY_LOG(info, "Server started.");
	return 0;
}
