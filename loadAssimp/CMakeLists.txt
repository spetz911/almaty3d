cmake_minimum_required(VERSION 3.1)
project(loadAssimp)

FIND_LIBRARY(OPENGL_LIBRARY OpenGL)
FIND_LIBRARY(GLUT_LIBRARY GLUT)
find_package(ZLIB REQUIRED)

add_executable(${PROJECT_NAME} SampleOpenGL.c $<TARGET_OBJECTS:assimp_master>)

target_link_libraries(${PROJECT_NAME} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${ZLIB_LIBRARY})

include_directories(../ThirdParty/assimp/include)



set(OTHER_FILES
    dwarf.x
    )


if(NOT ${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})

    foreach(FILEX ${OTHER_FILES})
        add_custom_command(
           TARGET ${PROJECT_NAME} POST_BUILD
           COMMAND ${CMAKE_COMMAND} -E copy
           "${CMAKE_CURRENT_SOURCE_DIR}/${FILEX}"
           "${CMAKE_CURRENT_BINARY_DIR}/${FILEX}"
        )
    endforeach(FILEX)

endif()
