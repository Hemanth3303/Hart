add_library(stb STATIC
	"src/stb_image.c"
	"include/stb_image.h"
)

set_target_properties(stb PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
	C_STANDARD 17
	C_STANDARD_REQUIRED ON
	C_EXTENSIONS OFF
	POSITION_INDEPENDENT_CODE ON
	OUTPUT_NAME stb
)

target_include_directories(stb PUBLIC
	${PROJECT_SOURCE_DIR}/vendor/stb/include
)

target_compile_definitions(stb PRIVATE
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_compile_definitions(stb PRIVATE
		NOMINMAX
		_CRT_SECURE_NO_WARNINGS
		WIN32_LEAN_AND_MEAN
	)
	if (MSVC)
		target_compile_options(stb PRIVATE
			/Zc:__cplusplus
		)
	elseif (MINGW)
		target_link_libraries(stb PRIVATE
			m
		)
		target_link_options(stb PRIVATE
			-static
			-static-libgcc
			-static-libstdc++
		)
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(stb PRIVATE
			# clang stuff
		)
		target_link_options(stb PRIVATE
			-static
		)
	endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_definitions(stb PRIVATE
	)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		target_link_libraries(stb PRIVATE
			dl
			m
  			pthread
		)
		target_link_options(stb PRIVATE
			-static
			-static-libgcc
			-static-libstdc++
		)
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(stb PRIVATE
			# clang stuff
		)
		target_link_options(stb PRIVATE
			-static
		)
	endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	target_compile_definitions(stb PRIVATE
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "CXX flags" FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEBUG}" CACHE STRING "C flags" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING "Linker flags" FORCE)
	target_compile_definitions(stb PRIVATE
		DEBUG
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "CXX flags" FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_RELEASE}" CACHE STRING "C flags" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_RELEASE}" CACHE STRING "Linker flags" FORCE)
	target_compile_definitions(stb PRIVATE
		NDEBUG
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Dist)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "CXX flags" FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_RELEASE}" CACHE STRING "C flags" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_RELEASE}" CACHE STRING "Linker flags" FORCE)

	target_compile_definitions(stb PRIVATE
		NDEBUG
	)
endif()