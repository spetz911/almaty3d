cmake_minimum_required(VERSION 3.1)
project(tutorial18_billboards_and_particles)

SET(SOURCE_FILE tutorial18_particles.cpp)

add_executable(tutorial18_particles tutorial18_particles.cpp $<TARGET_OBJECTS:Common>)
add_executable(tutorial18_billboards tutorial18_billboards.cpp $<TARGET_OBJECTS:Common>)


target_link_libraries(tutorial18_particles ${GLFW_LIBRARY} ${OPENGL_LIBRARY})
target_link_libraries(tutorial18_billboards ${GLFW_LIBRARY} ${OPENGL_LIBRARY})


set(OTHER_FILES
    Billboard.fragmentshader
    ExampleBillboard.DDS
    particle.DDS
    Billboard.vertexshader
    Particle.fragmentshader
    Particle.vertexshader
    )


if(NOT ${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})

    foreach(FILEX ${OTHER_FILES})
        add_custom_command(
           TARGET tutorial18_particles POST_BUILD
           COMMAND ${CMAKE_COMMAND} -E copy
           "${CMAKE_CURRENT_SOURCE_DIR}/${FILEX}"
           "${CMAKE_CURRENT_BINARY_DIR}/${FILEX}"
        )

        add_custom_command(
           TARGET tutorial18_billboards POST_BUILD
           COMMAND ${CMAKE_COMMAND} -E copy
           "${CMAKE_CURRENT_SOURCE_DIR}/${FILEX}"
           "${CMAKE_CURRENT_BINARY_DIR}/${FILEX}"
        )
    endforeach(FILEX)

endif()
