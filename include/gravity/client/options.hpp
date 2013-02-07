/*
 * client/options.hpp
 *
 * Configuration for the client module.
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#ifndef GRAVITY_CLIENT_OPTIONS_HPP
#define GRAVITY_CLIENT_OPTIONS_HPP

#include <istream>

#include <boost/utility.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/program_options.hpp>

namespace Gravity {
namespace Client {

class Options : private boost::noncopyable {
public:
    bool	fullscreen;
    int     hres;
    int     vres;
    int     msaa;
    int     bitdepth;
    int     circleDetail;
    bool    wireframe;
	float	renderscale;

private:
    boost::program_options::options_description commandDescription;
    boost::program_options::options_description iniDescription;
    
    static boost::mutex mutex;
    Options();

public:
    static Options& GetInstance();
    void LoadFromCommandLine(int argc, char *argv[]);
    void LoadFromIniFile(std::istream& input);
}; 

} // namespace Client
} // namespace Gravity

#endif /* GRAVITY_CLIENT_OPTIONS_HPP */
