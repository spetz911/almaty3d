cmake_minimum_required(VERSION 3.1)
project(tutorial08)

#message(WARNING "OLOLO1 = ${CMAKE_CURRENT_BINARY_DIR}")

set(SOURCE_FILES
    tutorial08.cpp
    common/shader.cpp
    common/texture.cpp
    common/controls.cpp
    common/objloader.cpp
    )

set(SHADERS_FILES
    StandardShading.vertexshader
    StandardShading.fragmentshader)

set(OTHER_FILES
    data/suzanne.obj
    data/uvmap.DDS
    )


include_directories(/opt/local/include)

FIND_LIBRARY(GLFW_LIBRARY GLFW)
FIND_LIBRARY(OPENGL_LIBRARY OpenGL)

add_executable(tutorial08 ${SOURCE_FILES} ${SHADERS_FILES})

target_link_libraries(tutorial08 ${OPENGL_LIBRARY} ${GLFW_LIBRARY})


ADD_CUSTOM_COMMAND(TARGET tutorial08 POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/data)

foreach(FILEX ${SHADERS_FILES} ${OTHER_FILES})
    add_custom_command(
       TARGET tutorial08 POST_BUILD
       COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_CURRENT_SOURCE_DIR}/${FILEX}"
       "${CMAKE_CURRENT_BINARY_DIR}/${FILEX}"
    )
endforeach(FILEX)
