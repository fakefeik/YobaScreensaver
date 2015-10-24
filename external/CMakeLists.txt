if(MSVC AND NOT "${MSVC_VERSION}" LESS 1400)
	add_definitions("/MP")
endif()

### GLFW ###

add_subdirectory (glfw)

include_directories(
	glfw/include/GLFW/
	glew/include/
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(OPENGL_LIBRARY
		${OPENGL_LIBRARY}
		-lGL -lGLU -lXrandr -lXext -lX11 -lrt
		${CMAKE_DL_LIBS}
		${GLFW_LIBRARIES}
	)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(OPENGL_LIBRARY
		${OPENGL_LIBRARY}
		${CMAKE_DL_LIBS}
		${GLFW_LIBRARIES}
	)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

### GLEW ###

set(GLEW_SOURCE glew/src/glew.c)
add_library(GLEW STATIC	${GLEW_SOURCE})
target_link_libraries(GLEW ${OPENGL_LIBRARY})
