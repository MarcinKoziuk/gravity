/*
 * gravity.hpp
 *
 * Top-level definitions for every module.
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#ifndef GRAVITY_CONFIG_HPP
#define GRAVITY_CONFIG_HPP

#define GRAVITY_STRINGIFY_(x) #x
#define GRAVITY_STRINGIFY(x) GRAVITY_STRINGIFY_(x)

#define GRAVITY_VERSION_MAJOR 0
#define GRAVITY_VERSION_MINOR 1
#define GRAVITY_BRANCH CURRENT

#define GRAVITY_VERSION \
    GRAVITY_VERSION_MAJOR.GRAVITY_VERSION_MINOR-GRAVITY_BRANCH

#define GRAVITY_VERSION_STRING GRAVITY_STRINGIFY(GRAVITY_VERSION)

#define GRAVITY_PROGRAM_NAME Gravity

#endif /* GRAVITY_GAME_HPP */
