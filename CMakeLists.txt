cmake_minimum_required(VERSION 3.26)
project("Hart" LANGUAGES CXX C)

include(cmake/base/config.cmake)
include(cmake/base/utils.cmake)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(HART_IS_SUBMODULE FALSE)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	set(HART_IS_SUBMODULE FALSE)
else()
	set(HART_IS_SUBMODULE TRUE)
endif()

print(CMAKE_BUILD_TYPE)
print(HART_IS_SUBMODULE)
print(CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
print(CMAKE_LIBRARY_OUTPUT_DIRECTORY)
print(CMAKE_RUNTIME_OUTPUT_DIRECTORY)

add_subdirectory("vendor/glad")
add_subdirectory("vendor/glfw")
add_subdirectory("vendor/stb")
add_subdirectory("vendor/miniaudio")
add_subdirectory("Hart-Engine")

if(NOT HART_IS_SUBMODULE)
	add_subdirectory("Examples/Two-Player-Pong")
	add_subdirectory("Sandbox")
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)
endif(NOT HART_IS_SUBMODULE)