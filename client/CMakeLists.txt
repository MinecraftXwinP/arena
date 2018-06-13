cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)

find_package(
    SDL2
    REQUIRED
)

find_package(PkgConfig)

if (PKG_CONFIG_FOUND)
pkg_check_modules(SDL2_IMAGE sdl2_image)
endif()

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
    camera.cpp
    camera.hpp
    render_engine.cpp
    render_engine.hpp
    util/file.cpp
    util/file.hpp
    exception/gl_exception.cpp
    exception/gl_exception.hpp
    exception/gl_shader_compile_exception.cpp
    exception/gl_shader_compile_exception.hpp
    camera_controller.cpp
    camera_controller.hpp

)

target_link_libraries(
    arena
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLM_LIBRARIES}
)
target_include_directories(
    arena
    PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
)

add_custom_command(
    TARGET arena
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shader $<TARGET_FILE_DIR:arena>/shader
)
