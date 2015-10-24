cmake_minimum_required (VERSION 2.6)
project (YobaScreensaver)

find_package(OpenGL REQUIRED)

add_subdirectory(external)

include_directories(
	external/glfw/include/
	external/glm/
	external/glew/include/
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW
)

add_executable(YobaScreensaver 
	src/main.cpp
	src/main.h
	src/bytes.h
	src/cube.cpp
	src/mesh.cpp
	src/mesh.h
	src/shader.cpp
	src/shader.h
	src/texture.cpp
	src/texture.h
)

target_link_libraries(YobaScreensaver ${ALL_LIBS})

set_target_properties(YobaScreensaver PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/YobaScreensaver/")
