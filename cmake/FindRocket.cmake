# Finds the Rocket library

# Module defines:
# ROCKET_INCLUDE_DIR
# ROCKET_LIBRARIES
# ROCKET_FOUND

# Initially not found
set( ROCKET_FOUND 0 )

# Find the path for the directory
find_path( ROCKET_INCLUDE_DIR
        NAMES
                Rocket/Core.h
        PATHS
                /usr/include
                /usr/local/include
                ${ROCKET_ROOT}
                $ENV{ROCKET_ROOT}
        DOC
                "Specify include directory that will contain Rocket/Core.h"
)

# Library directory
find_library( ROCKET_CORE_LIBRARY
        NAMES
                RocketCore
        PATHS
                /usr/lib
                /usr/local/lib
                ${ROCKET_ROOT}
                $ENV{ROCKET_ROOT}
)
find_library( ROCKET_CONTROLS_LIBRARY
        NAMES
                RocketControls
        PATHS
                /usr/lib
                /usr/local/lib
                ${ROCKET_ROOT}
                $ENV{ROCKET_ROOT}
)
find_library( ROCKET_DEBUGGER_LIBRARY
        NAMES
                RocketDebugger
        PATHS
                /usr/lib
                /usr/local/lib
                ${ROCKET_ROOT}
                $ENV{ROCKET_ROOT}
)
set(ROCKET_LIBRARIES ${ROCKET_CORE_LIBRARY} ${ROCKET_CONTROLS_LIBRARY} ${ROCKET_DEBUGGER_LIBRARY})

# Test
if( ROCKET_LIBRARIES )
        if( ROCKET_INCLUDE_DIR )
                set( ROCKET_FOUND 1 )
                message( STATUS "Found ROCKET Library: ${ROCKET_LIBRARIES}" )
                message( STATUS "Found ROCKET Ogre Library: ${ROCKET_OGRE_LIBRARIES}" )
                message( STATUS "Found ROCKET Headers: ${ROCKET_INCLUDE_DIR}" )
        else()
                message( FATAL_ERROR "Could not find ROCKET headers!  Please install ROCKET." )
        endif()
endif()

# Mark it as advanced
mark_as_advanced( ROCKET_FOUND ROCKET_LIBRARIES ROCKET_INCLUDE_DIR )
  
