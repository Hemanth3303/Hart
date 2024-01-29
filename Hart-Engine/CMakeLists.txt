file(GLOB_RECURSE HartEngineSrc CONFIGURE_DEPENDS "*.h" "*.c" "*.hpp" "*.cpp")

add_library(Hart-Engine STATIC
	${HartEngineSrc}
)

set_target_properties(Hart-Engine PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
	C_STANDARD 17
	C_STANDARD_REQUIRED ON
	C_EXTENSIONS OFF
	POSITION_INDEPENDENT_CODE ON
	OUTPUT_NAME Hart-Engine
)

target_include_directories(Hart-Engine PUBLIC
	${PROJECT_SOURCE_DIR}/Hart-Engine/src
	${PROJECT_SOURCE_DIR}/vendor/glfw/include
	${PROJECT_SOURCE_DIR}/vendor/glad/include
	${PROJECT_SOURCE_DIR}/vendor/stb/include
)

target_link_libraries(Hart-Engine PUBLIC 
	glfw
	glad
	stb
)

target_compile_definitions(Hart-Engine PRIVATE
	HART_ENGINE
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_compile_definitions(Hart-Engine PRIVATE
		NOMINMAX
		_CRT_SECURE_NO_WARNINGS
		WIN32_LEAN_AND_MEAN
		HART_WINDOWS
	)
	if (MSVC)
		target_compile_options(Hart-Engine PRIVATE
			/Zc:__cplusplus
		)
	elseif (MINGW)
		target_link_libraries(Hart-Engine PRIVATE
			m
		)
		target_link_options(Hart-Engine PRIVATE
			-static
			-static-libgcc
			-static-libstdc++
		)
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(Hart-Engine PRIVATE
			# clang stuff
		)
		target_link_options(Hart-Engine PRIVATE
			-static
		)
	endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_definitions(Hart-Engine PRIVATE
		HART_LINUX
	)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		target_link_libraries(Hart-Engine PRIVATE
			dl
			m
  			pthread
		)
		target_link_options(Hart-Engine PRIVATE
			-static
			-static-libgcc
			-static-libstdc++
		)
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(Hart-Engine PRIVATE
			# clang stuff
		)
		target_link_options(Hart-Engine PRIVATE
			-static
		)
	endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	target_compile_definitions(Hart-Engine PRIVATE
		HART_OSX
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "CXX flags" FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEBUG}" CACHE STRING "C flags" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING "Linker flags" FORCE)
	target_compile_definitions(Hart-Engine PRIVATE
		HART_DEBUG
		DEBUG
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "CXX flags" FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_RELEASE}" CACHE STRING "C flags" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_RELEASE}" CACHE STRING "Linker flags" FORCE)
	target_compile_definitions(Hart-Engine PRIVATE
		HART_RELEASE
		NDEBUG
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Dist)
	remove_definitions(-DHART_RELEASE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "CXX flags" FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_RELEASE}" CACHE STRING "C flags" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_RELEASE}" CACHE STRING "Linker flags" FORCE)

	target_compile_definitions(Hart-Engine PRIVATE
		HART_DIST
	)
endif()