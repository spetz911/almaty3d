cmake_minimum_required(VERSION 3.1)
project(tutorial01_first_window)

SET(SOURCE_FILE tutorial01.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILE} $<TARGET_OBJECTS:Common>)

target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY} ${OPENGL_LIBRARY})
