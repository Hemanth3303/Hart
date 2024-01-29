file(GLOB_RECURSE Sandbox CONFIGURE_DEPENDS "*.h" "*.c" "*.hpp" "*.cpp")

add_executable(Sandbox
	${Sandbox}
)
set_target_properties(Sandbox PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
	C_STANDARD 17
	C_STANDARD_REQUIRED ON
	C_EXTENSIONS OFF
	POSITION_INDEPENDENT_CODE ON
	OUTPUT_NAME Sandbox
)

target_include_directories(Sandbox PUBLIC
	${PROJECT_SOURCE_DIR}/Sandbox/src
	${PROJECT_SOURCE_DIR}/Hart-Engine/src
	${PROJECT_SOURCE_DIR}/vendor/glfw/include
	${PROJECT_SOURCE_DIR}/vendor/glad/include
	${PROJECT_SOURCE_DIR}/vendor/stb/include
)

target_link_libraries(Sandbox PUBLIC
	Hart-Engine
)

target_compile_definitions(Sandbox PRIVATE
	SANDBOX
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_compile_definitions(Sandbox PRIVATE
		NOMINMAX
		_CRT_SECURE_NO_WARNINGS
		WIN32_LEAN_AND_MEAN
		SANDBOX_WINDOWS
	)
	if (MSVC)
		target_compile_options(Sandbox PRIVATE
			/Zc:__cplusplus
		)
	elseif (MINGW)
		target_link_libraries(Sandbox PRIVATE
			m
		)
		target_link_options(Sandbox PRIVATE
			-static
			-static-libgcc
			-static-libstdc++
		)
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(Sandbox PRIVATE
			# clang stuff
		)
		target_link_options(Sandbox PRIVATE
			-static
		)
	endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_definitions(Sandbox PRIVATE
		SANDBOX_LINUX
	)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		target_link_libraries(Sandbox PRIVATE
			dl
			m
  			pthread
		)
		target_link_options(Sandbox PRIVATE
			-static
			-static-libgcc
			-static-libstdc++
		)
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(Sandbox PRIVATE
			# clang stuff
		)
		target_link_options(Sandbox PRIVATE
			-static
		)
	endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	target_compile_definitions(Sandbox PRIVATE
		SANDBOX_OSX
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "CXX flags" FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEBUG}" CACHE STRING "C flags" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING "Linker flags" FORCE)
	target_compile_definitions(Sandbox PRIVATE
		SANDBOX_DEBUG
		HART_DEBUG
		DEBUG
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "CXX flags" FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_RELEASE}" CACHE STRING "C flags" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_RELEASE}" CACHE STRING "Linker flags" FORCE)
	target_compile_definitions(Sandbox PRIVATE
		SANDBOX_RELEASE
		HART_RELEASE
		NDEBUG
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Dist)
	remove_definitions(-DSANDBOX_RELEASE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "CXX flags" FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_RELEASE}" CACHE STRING "C flags" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_RELEASE}" CACHE STRING "Linker flags" FORCE)

	target_compile_definitions(Sandbox PRIVATE
		SANDBOX_DIST
		HART_DIST
		NDEBUG
	)
endif()

add_custom_command(
	TARGET Sandbox POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${PROJECT_SOURCE_DIR}/Sandbox/res
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res
	COMMENT "Copying resource folder to binary directory"
)
