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

find_package(
    GLM
    REQUIRED
)

add_executable(
    arena
    client.cpp
    render_engine.cpp
    render_engine.hpp
    util/file.cpp
    util/file.hpp
    exception/gl_exception.cpp
    exception/gl_exception.hpp
    exception/gl_shader_compile_exception.cpp
    exception/gl_shader_compile_exception.hpp

)

target_link_libraries(
    arena
    ${SDL2_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLM_LIBRARIES}
)
target_include_directories(
    arena
    PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
)

add_custom_command(
    TARGET arena
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shader $<TARGET_FILE_DIR:arena>/shader
)

include(ExternalProject)

# ExternalProject_Add(
#     ftgl
#     SVN_REPOSITORY svn://svn.code.sf.net/p/ftgl/code/trunk
#     CONFIGURE_COMMAND ./autogen.sh COMMAND ./configure
#     BUILD_IN_SOURCE 1
#     BUILD_COMMAND make
# )
