/*
 * game/logging.cpp
 *
 * Initializes the logging mechanism with boost::log
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#include <gravity/game/logging.hpp>
/*
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/log/expressions/attr.hpp>
#include <boost/log/expressions/message.hpp>
#include <boost/log/expressions/formatters/format.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>

#include <boost/log/keywords/format.hpp>*/

namespace Gravity {
namespace Game {

void InitializeLogging()
{
    //boost::log::add_console_log();
	/*boost::log::init_log_to_console(std::clog,
		boost::log::keywords::format = boost::log::formatters::format("[%1%] %2%: %3%")
			% boost::log::formatters::date_time("TimeStamp", std::nothrow)
			% boost::log::formatters::attr< boost::log::trivial::severity_level >("Severity", std::nothrow)
			% boost::log::formatters::message());

	boost::log::add_common_attributes();*/
    
}

} // namespace Game
} // namespace Gravity
