cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)

find_package(
    SDL2
    REQUIRED
)
find_package(
    GLEW
    REQUIRED
)

find_package(
    OPENGL
    REQUIRED
)

add_executable(
    arena
    client.cpp
    render_engine.cpp
    render_engine.hpp
)

target_link_libraries(
    arena
    ${SDL2_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${OPENGL_LIBRARIES}
)
target_include_directories(
    arena
    PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
)

include(ExternalProject)

ExternalProject_Add(
    ftgl
    SVN_REPOSITORY svn://svn.code.sf.net/p/ftgl/code/trunk
    CONFIGURE_COMMAND ./autogen.sh COMMAND ./configure
    BUILD_IN_SOURCE 1
    BUILD_COMMAND make
)
