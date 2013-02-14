/*
 * game/log.hpp
 *
 * Clean macro for logging
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#ifndef GRAVITY_GAME_LOG_HPP
#define GRAVITY_GAME_LOG_HPP

#include <ostream>

#include <boost/format.hpp>

#define GRAVITY_LOG(loglvl, message) Gravity::Game::Logger::getLogger().createStream(Gravity::Game::Logger::loglvl) << boost::format(message) << "\n"

namespace Gravity {
namespace Game {

class Logger {
public:
	enum Level {
		debug,
		info,
		message,
		warning,
		error,
		fatal
	};

	static const char* LEVEL_STRINGS[];

	static Logger getLogger();

	std::ostream& createStream(Level loglvl);
};

void InitializeLogging();

} // namespace Game
} // namespace Gravity

#endif /* GRAVITY_GAME_LOG_HPP */
