/*
 * client/options.cpp
 *
 * Configuration for the client module.
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#include <cstdlib>
#include <iostream>

#include <gravity/gravity.hpp>

#include <gravity/game/logging.hpp>
#include <gravity/game/util/option_assigner.hpp>

#include <gravity/client/options.hpp>

namespace po = boost::program_options;
using namespace Gravity::Game;
using namespace Gravity::Client;

namespace Gravity {
namespace Client {

namespace {

void Validate(const Options& o);

} // namespace

boost::mutex Options::mutex;

Options::Options() :
	fullscreen(false),
	hres(800),
	vres(600),
	msaa(4),
	bitdepth(32),
	circleDetail(8),
	wireframe(false),
	renderscale(15.f),
	commandDescription("Allowed options:"),
	iniDescription()
{
	commandDescription.add_options()
		("help,h",                                  "produce help message")
		("version,v",                               "show program version")
		("hres",                po::value<int>(),   "horizontal resolution")
		("vres",                po::value<int>(),   "vertical resolution")
		("bitdepth",            po::value<int>(),   "bit depth")
		("msaa-level",          po::value<int>(),   "anti-aliasing level")
		("circle-detail",       po::value<int>(),   "circle polygon detail")
		("fullscreen",                              "launches in full screen")
		("windowed",                                "launches windowed")
		("wireframe",           po::value<int>(),   "toggle wireframe polygons")
		("renderscale",         po::value<float>(), "default scale to render");

	iniDescription.add_options()
		("Screen.fullscreen",   po::value<bool>())
		("Screen.hres",         po::value<int>())
		("Screen.vres",         po::value<int>())
		("Screen.bitdepth",     po::value<int>())
		("Screen.msaa-level",   po::value<int>())
		("Draw.circle-detail",  po::value<int>())
		("Draw.wireframe",      po::value<bool>())
		("Draw.renderscale",    po::value<float>());
}

void Options::LoadFromCommandLine(int argc, char *argv[])
{
	po::variables_map map;

	try {
		po::store(po::parse_command_line(argc, argv, commandDescription), map);
	} catch (std::exception&) {
		std::cout << "Invalid command line arguments.\n";
		std::cout << commandDescription;
		std::exit(0);
	}

	po::notify(map);
	OptionAssigner::assign(map)
		("hres",            hres)
		("vres",            vres)
		("bitdepth",        bitdepth)
		("msaa-level",      msaa)
		("circle-detail",   circleDetail)
		("fullscreen",      fullscreen,     true)
		("windowed",        fullscreen,     false)
		("wireframe",       wireframe)
		("renderscale",		renderscale);

	if (map.count("help")) {
		std::cout << commandDescription;
		std::exit(0);
	}

	if (map.count("version")) {
		std::cout << GRAVITY_VERSION_STRING;
		std::exit(0);
	}

	Validate(*this);
}

void Options::LoadFromIniFile(std::istream& input)
{
	po::variables_map map;
	try {
		po::store(po::parse_config_file(input, iniDescription, true), map);
	} catch (std::exception& e) {
		//GRAVITY_LOG(fatal, "Could not parse ini file: %1%") % e.what();
	}

	po::notify(map);
	OptionAssigner::assign(map)
		("Screen.hres",             hres)
		("Screen.vres",             vres)
		("Screen.bitdepth",         bitdepth)
		("Screen.msaa-level",       msaa)
		("Screen.circle-detail",    circleDetail)
		("Draw.fullscreen",         fullscreen)
		("Draw.wireframe",          wireframe)
		("Draw.renderscale",        renderscale);
}

Options& Options::GetInstance()
{
	boost::mutex::scoped_lock lock(mutex);
	static Options instance;
	return instance;
}

namespace {

void Validate(const Options& o)
{
	if (o.bitdepth != 16 && o.bitdepth != 32) {
		std::cout << "Invalid bitdepth";
		std::exit(0);
	}

	if (o.msaa != 0 && o.msaa != 2 && o.msaa != 4 && o.msaa != 8) {
		std::cout << "Invalid MSAA level";
		std::exit(0);
	}
}

} // namespace

} // namespace Client
} // namespace Gravity

