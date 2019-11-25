cmake_minimum_required (VERSION 3.10)

project(DabEngine)

set(CMAKE_CXX_FLAGS "-g")

option(BUILD_EXE "Build the Test exe" OFF)

include_directories("${CMAKE_SOURCE_DIR}/../includes")
link_directories("${CMAKE_SOURCE_DIR}/../libs")

# make lib
file(GLOB_RECURSE SOURCE "*.cpp")
add_library(DabEngine ${SOURCE})

target_link_libraries(DabEngine glfw3)
target_link_libraries(DabEngine glew32)
target_link_libraries(DabEngine opengl32)

if(BUILD_EXE)
	# make exe
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin )

	add_executable(EXE Main.cpp)

	target_link_libraries(EXE DabEngine)
endif(BUILD_EXE)