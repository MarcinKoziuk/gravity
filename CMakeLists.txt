cmake_minimum_required(VERSION 2.6)
project(GRAVITY)

option(GRAVITY_STATIC_VARIANT "Build static and minimal variant" OFF)

set(GRAVITY_LIBRARY gravity)
set(GRAVITY_GAME_LIBRARY game)
set(GRAVITY_SERVER_EXECUTABLE server)
set(GRAVITY_CLIENT_EXECUTABLE client)

set(GRAVITY_VERSION "0_1-CURRENT")
set(GRAVITY_DEVKIT_PATH $ENV{GRAVITY_DEVKIT})

if (WIN32)
    string(REGEX REPLACE "\\\\" "/" GRAVITY_DEVKIT_PATH ${GRAVITY_DEVKIT_PATH})
    message(STATUS "Detected devkit path: `${GRAVITY_DEVKIT_PATH}'")
endif()

file(GLOB GRAVITY_H "include/gravity/*.hpp")
file(GLOB GRAVITY_SRC "src/*.cpp")
file(GLOB GRAVITY_GAME_SRC "src/game/*.cpp")
file(GLOB GRAVITY_GAME_H "include/gravity/game/*.hpp")
file(GLOB GRAVITY_GAME_MATH_SRC "src/game/math/*.cpp")
file(GLOB GRAVITY_GAME_MATH_H "include/gravity/game/math/*.hpp")
file(GLOB GRAVITY_GAME_UTIL_SRC "src/game/util/*.cpp")
file(GLOB GRAVITY_GAME_UTIL_H "include/gravity/game/util/*.hpp")
file(GLOB GRAVITY_GAME_RESOURCE_SRC "src/game/resource/*.cpp")
file(GLOB GRAVITY_GAME_RESOURCE_H "include/gravity/game/resource/*.hpp")
file(GLOB GRAVITY_SERVER_SRC "src/server/*.cpp")
file(GLOB GRAVITY_SERVER_H "include/gravity/server/*.hpp")
file(GLOB GRAVITY_CLIENT_SRC "src/client/*.cpp")
file(GLOB GRAVITY_CLIENT_H "include/gravity/client/*.hpp")
file(GLOB GRAVITY_CLIENT_RENDER_SRC "src/client/render/*.cpp")
file(GLOB GRAVITY_CLIENT_RENDER_H "include/gravity/client/render/*.hpp")
file(GLOB GRAVITY_CLIENT_UI_SRC "src/client/ui/*.cpp")
file(GLOB GRAVITY_CLIENT_UI_H "include/gravity/client/ui/*.hpp")

add_custom_target(${GRAVITY_LIBRARY} SOURCES ${GRAVITY_H})
add_library(${GRAVITY_GAME_LIBRARY} STATIC
            ${GRAVITY_GAME_SRC} ${GRAVITY_GAME_H}
            ${GRAVITY_GAME_MATH_SRC} ${GRAVITY_GAME_MATH_H}
            ${GRAVITY_GAME_UTIL_SRC} ${GRAVITY_GAME_UTIL_H}
            ${GRAVITY_GAME_RESOURCE_SRC} ${GRAVITY_GAME_RESOURCE_H})
add_executable(${GRAVITY_CLIENT_EXECUTABLE}
            ${GRAVITY_CLIENT_SRC} ${GRAVITY_CLIENT_H}
            ${GRAVITY_CLIENT_RENDER_SRC} ${GRAVITY_CLIENT_RENDER_H}
            ${GRAVITY_CLIENT_UI_SRC} ${GRAVITY_CLIENT_UI_H})
add_executable(${GRAVITY_SERVER_EXECUTABLE} ${GRAVITY_SERVER_SRC} ${GRAVITY_SERVER_H})

include_directories("include/")

target_link_libraries(${GRAVITY_CLIENT_EXECUTABLE} ${GRAVITY_GAME_LIBRARY})
target_link_libraries(${GRAVITY_SERVER_EXECUTABLE} ${GRAVITY_GAME_LIBRARY})

set(GRAVITY_GAME_FLAGS "-DGRAVITY_GAME")
set(GRAVITY_CLIENT_FLAGS "${GRAVITY_GAME_FLAGS} -DGRAVITY_CLIENT")
set(GRAVITY_SERVER_FLAGS "${GRAVITY_GAME_FLAGS} -DGRAVITY_SERVER")
if (NOT GRAVITY_STATIC_VARIANT)
    set(GRAVITY_GAME_FLAGS "${GRAVITY_GAME_FLAGS} -DGRAVITY_GAME_EXPORTS")
    set(GRAVITY_CLIENT_FLAGS "${GRAVITY_CLIENT_FLAGS} -DGRAVITY_CLIENT_EXPORTS")
endif()

set_target_properties(${GRAVITY_GAME_LIBRARY} PROPERTIES COMPILE_FLAGS ${GRAVITY_GAME_FLAGS})
set_target_properties(${GRAVITY_CLIENT_EXECUTABLE} PROPERTIES COMPILE_FLAGS ${GRAVITY_CLIENT_FLAGS})
set_target_properties(${GRAVITY_SERVER_EXECUTABLE} PROPERTIES COMPILE_FLAGS ${GRAVITY_SERVER_FLAGS})

source_group("Header files" FILES ${GRAVITY_H})
source_group("Source files" FILES ${GRAVITY_SRC})
source_group("Source files" FILES ${GRAVITY_GAME_SRC})
source_group("Header files" FILES ${GRAVITY_GAME_H})
source_group("Header files\\math" FILES ${GRAVITY_GAME_MATH_H})
source_group("Source files\\math" FILES ${GRAVITY_GAME_MATH_SRC})
source_group("Header files\\util" FILES ${GRAVITY_GAME_UTIL_H})
source_group("Source files\\util" FILES ${GRAVITY_GAME_UTIL_SRC})
source_group("Header files\\resource" FILES ${GRAVITY_GAME_RESOURCE_H})
source_group("Source files\\resource" FILES ${GRAVITY_GAME_RESOURCE_SRC})
source_group("Source files" FILES ${GRAVITY_SERVER_SRC})
source_group("Header files" FILES ${GRAVITY_SERVER_H})
source_group("Source files" FILES ${GRAVITY_CLIENT_SRC})
source_group("Header files" FILES ${GRAVITY_CLIENT_H})
source_group("Source files\\render" FILES ${GRAVITY_CLIENT_RENDER_SRC})
source_group("Header files\\render" FILES ${GRAVITY_CLIENT_RENDER_H})
source_group("Source files\\ui" FILES ${GRAVITY_CLIENT_UI_SRC})
source_group("Header files\\ui" FILES ${GRAVITY_CLIENT_UI_H})

if(WIN32)
    include_directories(SYSTEM "${GRAVITY_DEVKIT_PATH}/_Include")

    macro(devkit_link_library TARGET_NAME LIB_NAME LIB_VERSION REL_SUFFIX DEB_SUFFIX)
        target_link_libraries(${TARGET_NAME} debug "${GRAVITY_DEVKIT_PATH}/_Libraries/lib${LIB_NAME}_${LIB_VERSION}${DEB_SUFFIX}"
                                             optimized "${GRAVITY_DEVKIT_PATH}/_Libraries/lib${LIB_NAME}_${LIB_VERSION}${REL_SUFFIX}"
        )
    endmacro()

    macro(devkit_link_all_libraries SHARED_LIB_REL_SUFFIX STATIC_LIB_REL_SUFFIX
                                    SHARED_LIB_DEB_SUFFIX STATIC_LIB_DEB_SUFFIX)
        devkit_link_library(${GRAVITY_GAME_LIBRARY} box2d 2_1_0 ${STATIC_LIB_REL_SUFFIX} ${STATIC_LIB_DEB_SUFFIX})
        devkit_link_library(${GRAVITY_GAME_LIBRARY} boost_program_options 1_49 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
        devkit_link_library(${GRAVITY_GAME_LIBRARY} boost_log 2 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
        devkit_link_library(${GRAVITY_GAME_LIBRARY} boost_thread 1_49 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
        devkit_link_library(${GRAVITY_GAME_LIBRARY} boost_system 1_49 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
        devkit_link_library(${GRAVITY_GAME_LIBRARY} boost_filesystem 1_49 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
        devkit_link_library(${GRAVITY_GAME_LIBRARY} boost_date_time 1_49 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
        devkit_link_library(${GRAVITY_CLIENT_EXECUTABLE} freetype 2_4_8 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
        devkit_link_library(${GRAVITY_CLIENT_EXECUTABLE} glew 1_7_0 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
        devkit_link_library(${GRAVITY_CLIENT_EXECUTABLE} jpeg 8d ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
        devkit_link_library(${GRAVITY_CLIENT_EXECUTABLE} rocket_core 1_2_1 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
        devkit_link_library(${GRAVITY_CLIENT_EXECUTABLE} rocket_debugger 1_2_1 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
        devkit_link_library(${GRAVITY_CLIENT_EXECUTABLE} rocket_controls 1_2_1 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
        devkit_link_library(${GRAVITY_CLIENT_EXECUTABLE} sfml_graphics 2_0_0 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
        devkit_link_library(${GRAVITY_CLIENT_EXECUTABLE} sfml_window 2_0_0 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
        devkit_link_library(${GRAVITY_CLIENT_EXECUTABLE} sfml_audio 2_0_0 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
        devkit_link_library(${GRAVITY_GAME_LIBRARY} sfml_system 2_0_0 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
        devkit_link_library(${GRAVITY_GAME_LIBRARY} sfml_network 2_0_0 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
    endmacro()
	
	target_link_libraries(${GRAVITY_CLIENT_EXECUTABLE} opengl32)

    if (GRAVITY_STATIC_VARIANT==ON)
        message("Notice: build the static variant with MinSizeRel.")
        if (MSVC)
            devkit_link_all_libraries(
                "-vc100-mt-smin-x86.lib"
                "-vc100-mt-smin-x86.lib"
                "-vc100-mt-sgd-x86.lib"
                "-vc100-mt-sgd-x86.lib"
            )
        else()
            devkit_link_all_libraries(
                "-gcc-smin-x86.a"
                "-gcc-smin-x86.a"
                "-gcc-sd-x86.a"
                "-gcc-sd-x86.a"
            )
        endif()

        add_definitions(-DSFML_STATIC -DSTATIC_LIB)
    else()
        if (MSVC)
            devkit_link_all_libraries(
                "-vc100-mtd-x86.lib"
                "-vc100-mtd-s-x86.lib"
                "-vc100-mtd-gd-x86.lib"
                "-vc100-mtd-sgd-x86.lib"
            )
        else()
            devkit_link_all_libraries(
                "-gcc-x86.dll.a"
                "-gcc-s-x86.a"
                "-gcc-d-x86.dll.a"
                "-gcc-sd-x86.a"
            )
        endif()

        add_definitions(-DBOOST_ALL_DYN_LINK)
    endif()

    add_definitions(-DBOOST_ALL_NO_LIB)
else()
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
    find_package(Threads)
    find_package(OpenGL REQUIRED)
    find_package(Box2D REQUIRED)
    find_package(Boost COMPONENTS program_options thread system filesystem date_time)
    find_package(Freetype REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(JPEG REQUIRED)
    find_package(Rocket REQUIRED)
    find_package(SFML 2 COMPONENTS graphics window audio system network)
    
    include_directories(SYSTEM
        ${BOX2D_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        ${Freetype_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        ${JPEG_INCLUDE_DIR}
        ${Rocket_INCLUDE_DIR}
        ${SFML_INCLUDE_DIR}
    )
    
    target_link_libraries(${GRAVITY_GAME_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
    target_link_libraries(${GRAVITY_GAME_LIBRARY} ${BOX2D_LIBRARY})
    target_link_libraries(${GRAVITY_GAME_LIBRARY} ${Boost_LIBRARIES})
    target_link_libraries(${GRAVITY_GAME_LIBRARY} ${SFML_SYSTEM_LIBRARY})
    target_link_libraries(${GRAVITY_GAME_LIBRARY} ${SFML_NETWORK_LIBRARY})
    target_link_libraries(${GRAVITY_CLIENT_EXECUTABLE} ${OPENGL_LIBRARY})
    target_link_libraries(${GRAVITY_CLIENT_EXECUTABLE} ${Freetype_LIBRARY})
    target_link_libraries(${GRAVITY_CLIENT_EXECUTABLE} ${GLEW_LIBRARY})
    target_link_libraries(${GRAVITY_CLIENT_EXECUTABLE} ${ROCKET_LIBRARIES})
    target_link_libraries(${GRAVITY_CLIENT_EXECUTABLE} ${SFML_GRAPHICS_LIBRARY})
    target_link_libraries(${GRAVITY_CLIENT_EXECUTABLE} ${SFML_WINDOW_LIBRARY})
    target_link_libraries(${GRAVITY_CLIENT_EXECUTABLE} ${SFML_AUDIO_LIBRARY})


    
#         devkit_link_library(${GRAVITY_GAME_LIBRARY} box2d 2_1_0 ${STATIC_LIB_REL_SUFFIX} ${STATIC_LIB_DEB_SUFFIX})
#         devkit_link_library(${GRAVITY_GAME_LIBRARY} boost_program_options 1_49 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
#         devkit_link_library(${GRAVITY_GAME_LIBRARY} boost_log 2 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
#         devkit_link_library(${GRAVITY_GAME_LIBRARY} boost_thread 1_49 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
#         devkit_link_library(${GRAVITY_GAME_LIBRARY} boost_system 1_49 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
#         devkit_link_library(${GRAVITY_GAME_LIBRARY} boost_filesystem 1_49 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
#         devkit_link_library(${GRAVITY_GAME_LIBRARY} boost_date_time 1_49 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
#         devkit_link_library(${GRAVITY_CLIENT_EXECUTABLE} freetype 2_4_8 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
#         devkit_link_library(${GRAVITY_CLIENT_EXECUTABLE} glew 1_7_0 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
#         devkit_link_library(${GRAVITY_CLIENT_EXECUTABLE} jpeg 8d ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
#         devkit_link_library(${GRAVITY_CLIENT_EXECUTABLE} rocket_core 1_2_1 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
#         devkit_link_library(${GRAVITY_CLIENT_EXECUTABLE} rocket_debugger 1_2_1 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
#         devkit_link_library(${GRAVITY_CLIENT_EXECUTABLE} rocket_controls 1_2_1 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
#         devkit_link_library(${GRAVITY_CLIENT_EXECUTABLE} sfml_graphics 2_0_0 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
#         devkit_link_library(${GRAVITY_CLIENT_EXECUTABLE} sfml_window 2_0_0 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
#         devkit_link_library(${GRAVITY_GAME_LIBRARY} sfml_system 2_0_0 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
#         devkit_link_library(${GRAVITY_GAME_LIBRARY} sfml_network 2_0_0 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})
#         devkit_link_library(${GRAVITY_CLIENT_EXECUTABLE} sfml_audio 2_0_0 ${SHARED_LIB_REL_SUFFIX} ${SHARED_LIB_DEB_SUFFIX})

    
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /MP /fp:fast")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++98 -Wall -Wextra -pedantic")
endif()
