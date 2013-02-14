/*
 * game/logging.cpp
 *
 * Initializes the logging mechanism with boost::log
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#include <iostream>

#include <gravity/game/logging.hpp>

namespace Gravity {
namespace Game {

const char* Logger::LEVEL_STRINGS[] = {
	"DEBUG",
	"INFO",
	"MESSAGE",
	"WARNING",
	"ERROR",
	"FATAL"
};

Logger Logger::getLogger()
{
	return Logger();
}

std::ostream& Logger::createStream(Logger::Level loglvl)
{
	std::cout << Logger::LEVEL_STRINGS[loglvl] << ":";
	return std::cout;
}

} // namespace Game
} // namespace Gravity
