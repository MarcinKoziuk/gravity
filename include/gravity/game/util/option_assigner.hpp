/*
 * game/util/option_assigner.hpp
 *
 * Helper class for parsing values with boost::program_options
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#ifndef GRAVITY_GAME_OPTION_ASSIGNER_HPP
#define GRAVITY_GAME_OPTION_ASSIGNER_HPP

#include <functional>

#include <boost/program_options.hpp>

namespace Gravity {
namespace Game {

class OptionAssigner {
	boost::program_options::variables_map& map;

	OptionAssigner(boost::program_options::variables_map& map)
        : map(map)
	{}

public:
    static OptionAssigner assign(boost::program_options::variables_map& map)
    {
        return OptionAssigner(map);
    }


    template<class T>
	OptionAssigner& operator()(const std::string& string, T& variable)
	{
		if (map.count(string))
			variable = map[string].as<T>();
		return *this;
	}

    template<class T>
	OptionAssigner& operator()(const std::string& string, T& variable, T value)
	{
		if (map.count(string))
			variable = value;
		return *this;
	}
 };

 } // namespace Game
 } // namespace Gravity

#endif /* GRAVITY_GAME_OPTION_ASSIGNER_HPP */
