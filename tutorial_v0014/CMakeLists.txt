cmake_minimum_required(VERSION 3.1)
project(tutorial-all)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#// /System/Library/Frameworks/OpenGL.framework/Headers
#
#// clang++ -I.. -I/opt/local/include ../common/*.cpp  tutorial07.cpp
#// -L/opt/local/lib -lGLFW -framework OpenGL

include_directories(/opt/local/include)

FIND_LIBRARY(OPENGL_LIBRARY OpenGL)
FIND_LIBRARY(GLFW_LIBRARY GLFW)

set(COMMON_FILES
    common/shader.cpp
    common/texture.cpp
    common/controls.cpp
    common/objloader.cpp
    common/text2D.cpp
    common/vboindexer.cpp
    common/tangentspace.cpp
    common/quaternion_utils.cpp
    )

add_library(Common OBJECT ${COMMON_FILES} common/framework.hpp)

# basic:
add_subdirectory(tutorial01_first_window)
add_subdirectory(tutorial02_red_triangle)
add_subdirectory(tutorial03_matrices)
add_subdirectory(tutorial04_colored_cube)
add_subdirectory(tutorial05_textured_cube)
add_subdirectory(tutorial06_keyboard_and_mouse)
add_subdirectory(tutorial07_model_loading)
add_subdirectory(tutorial08_basic_shading)
# intermediate:
add_subdirectory(tutorial09_vbo_indexing)
add_subdirectory(tutorial10_transparency)
add_subdirectory(tutorial11_2d_fonts)
# TODO add_subdirectory(tutorial12_extensions)
add_subdirectory(tutorial13_normal_mapping)
add_subdirectory(tutorial14_render_to_texture)
add_subdirectory(tutorial15_lightmaps)
add_subdirectory(tutorial16_shadowmaps)
# TODO add_subdirectory(tutorial17_rotations)
add_subdirectory(tutorial18_billboards_and_particles)


