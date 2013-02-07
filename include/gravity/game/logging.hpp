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

//#include <boost/log/trivial.hpp>
#include <boost/format.hpp>

#define GRAVITY_LOG(loglvl, message) //BOOST_LOG_TRIVIAL(loglvl) << boost::format(message)

namespace Gravity {
namespace Game {

void InitializeLogging();

} // namespace Game
} // namespace Gravity

#endif /* GRAVITY_GAME_LOG_HPP */
