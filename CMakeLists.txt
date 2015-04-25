cmake_minimum_required(VERSION 3.1)
project(ogl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(OGL_SAMPLES_NAME ogl-samples)
set(FRAMEWORK_NAME framework)

enable_testing()

#CMAKE_BUILD_TOOL

if(CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)
	message(FATAL_ERROR "Source and binary directories must be different")
endif(CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)

if(("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
   OR (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel") AND UNIX))
	set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
	set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
	set(CMAKE_CXX_FLAGS "-std=c++11")
endif()

option(OGL_SAMPLES_IN_SOURCE_BUILD "OGL_SAMPLES_IN_SOURCE_BUILD" OFF)
if(OGL_SAMPLES_IN_SOURCE_BUILD)
	add_definitions(-DOGL_SAMPLES_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
	add_definitions(-DOGL_SAMPLES_BINARY_DIR="../")
else()
	add_definitions(-DOGL_SAMPLES_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
	add_definitions(-DOGL_SAMPLES_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}")
endif()

################################
# Add GLEW

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external)
add_definitions(-DGLEW_STATIC)

################################
# Add GLFW

set(GLFW_DIRECTORY glfw-3.1.1)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLFW_DIRECTORY}/include)

set(GLFW_INSTALL OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE STRING "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLFW_DIRECTORY})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLFW_DIRECTORY}/include)

################################
# Add freeimage

set(FREEIMAGE_BINARY_DIRECTORY "macosx")

set(FREEIMAGE_DIRECTORY FreeImage-3.15.4)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${FREEIMAGE_DIRECTORY})
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${FREEIMAGE_DIRECTORY}/${FREEIMAGE_BINARY_DIRECTORY})

add_definitions(-DFREEIMAGE_LIB)
set(FREEIMAGE_LIBRARY freeimage)
set(FREEIMAGE_BINARY_FILE freeimage)

set(FREEIMAGE_BIN_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/${FREEIMAGE_DIRECTORY}/${FREEIMAGE_BINARY_DIRECTORY}/${FREEIMAGE_BINARY_FILE})

################################
# Add GLM

set(GLM_DIRECTORY glm-0.9.7.A)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLM_DIRECTORY})

################################
# Add GLI

set(GLI_DIRECTORY gli-0.6.0.A)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLI_DIRECTORY})

################################
# Add GLO

set(GLO_DIRECTORY glo-0.1.0.0)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLO_DIRECTORY})

################################
# Add GLU

set(GLU_DIRECTORY glu-0.1.0.0)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLU_DIRECTORY})

################################
# Add EGL

set(EGL_DIRECTORY egl-1.4)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${EGL_DIRECTORY})

set(EGL_LIBRARY libEGL)

################################
# Add libraries to executables

set(BINARY_FILES glfw ${GLFW_LIBRARIES} ${FREEIMAGE_LIBRARY})

################################
# Add output directory

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/Debug )
else(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/Release )
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

################################
# Add options

option(OGL_SAMPLES_AUTOMATED_TESTS "OGL_SAMPLES_AUTOMATED_TESTS" OFF)
if(OGL_SAMPLES_AUTOMATED_TESTS)
	add_definitions(-DAUTOMATED_TESTS)
endif()

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
	if (NOT APPLE)
		add_definitions(-fpermissive)
	endif()
endif()

################################
# Add framework

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/framework)
add_subdirectory(framework)

################################
# Add subdirectory

add_subdirectory(src)

################################
# Add install

install (DIRECTORY data DESTINATION .)

# See http://www.vtk.org/Wiki/CMake:CPackPackageGenerators
set (CPACK_PACKAGE_VERSION_MAJOR "4")
set (CPACK_PACKAGE_VERSION_MINOR "5")
set (CPACK_PACKAGE_VERSION_PATCH "1")
# Use current date in YYYYMMDD format as patch number


set (CPACK_GENERATOR "TBZ2")

include(CPack)


FIND_LIBRARY(COCOA_LIBRARY Cocoa )
FIND_LIBRARY(IOKIT_LIBRARY IOKit )
FIND_LIBRARY(OPENGL_LIBRARY OpenGL)


add_executable(tryCocoa tryCocoa.m)

target_link_libraries(tryCocoa ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${OPENGL_LIBRARY})

add_subdirectory(tutorial08)

