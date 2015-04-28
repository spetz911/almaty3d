#function(glCreateSampleGTC NAME)
#	set(SAMPLE_NAME ${GL_PROFILE_GTC}-${GL_VERSION_GTC}-${NAME})
#	set(SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../data/${GL_PROFILE_GTC}-${GL_VERSION_GTC})
#
#	foreach(FILE ${GL_SHADER_GTC})
#		set(SHADER_PATH ${SHADER_PATH} ${SHADER_DIR}/${FILE})
#	endforeach(FILE)
#
#	source_group("Shader Files" FILES ${SHADER_PATH})
#
#	add_executable(${SAMPLE_NAME} ${GL_PROFILE_GTC}-${GL_VERSION_GTC}-${NAME}.cpp ${SHADER_PATH})
#	add_test(NAME ${SAMPLE_NAME} COMMAND $<TARGET_FILE:${SAMPLE_NAME}>)
#
#	target_link_libraries(${SAMPLE_NAME} ${FRAMEWORK_NAME} ${BINARY_FILES})
#	add_dependencies(${SAMPLE_NAME} glfw ${FRAMEWORK_NAME} ${COPY_BINARY})
#
#	install(TARGETS ${SAMPLE_NAME} DESTINATION .)
#endfunction(glCreateSampleGTC)

set(GL_PROFILE_GTC gl)
# OpenGL 4.1 samples
set(GL_VERSION_GTC 410)
set(GL_SHADER_GTC )

set(SAMPLE_NAME main)
set(SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../data/gl-${GL_VERSION_GTC})

foreach(FILE ${GL_SHADER_GTC})
	set(SHADER_PATH ${SHADER_PATH} ${SHADER_DIR}/${FILE})
endforeach(FILE)

source_group("Shader Files" FILES ${SHADER_PATH})

add_executable(${SAMPLE_NAME} main.cpp ${SHADER_PATH} )

target_link_libraries(${SAMPLE_NAME} ${FRAMEWORK_NAME} ${BINARY_FILES})
add_dependencies(${SAMPLE_NAME} glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS ${SAMPLE_NAME} DESTINATION .)


#set(GL_PROFILE_GTC gl)
## OpenGL 4.1 samples
#set(GL_VERSION_GTC 410)
#
#set(GL_SHADER_GTC )
#glCreateSampleGTC(caps)
#set(GL_SHADER_GTC viewport.vert viewport.geom viewport.frag layer.vert layer.geom layer.frag)
#glCreateSampleGTC(fbo-layered)
#set(GL_SHADER_GTC primitive-instancing.vert primitive-instancing.geom primitive-instancing.frag)
#glCreateSampleGTC(primitive-instanced)
