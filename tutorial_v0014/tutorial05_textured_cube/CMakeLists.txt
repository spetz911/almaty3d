cmake_minimum_required(VERSION 3.1)
project(tutorial05_textured_cube)

SET(SOURCE_FILE tutorial05.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILE} $<TARGET_OBJECTS:Common>)

target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY} ${OPENGL_LIBRARY})

set(OTHER_FILES
    uvtemplate.DDS
    TextureFragmentShader.fragmentshader
    uvtemplate.bmp
    TransformVertexShader.vertexshader
    uvtemplate.tga
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
