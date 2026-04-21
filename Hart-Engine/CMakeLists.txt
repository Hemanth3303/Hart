file(GLOB_RECURSE HART_ENGINE_SRC CONFIGURE_DEPENDS "*.h" "*.c" "*.hpp" "*.cpp")

add_library(Hart-Engine
	STATIC
	${HART_ENGINE_SRC}
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

target_link_libraries(Hart-Engine
	PUBLIC
		glfw
		glad
		stb
		miniaudio
	PRIVATE

)

target_include_directories(Hart-Engine
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CMAKE_SOURCE_DIR}/vendor/glad/include
		${CMAKE_SOURCE_DIR}/vendor/glfw/include
		${CMAKE_SOURCE_DIR}/vendor/miniaudio/include
		${CMAKE_SOURCE_DIR}/vendor/stb/include
	PRIVATE

)

target_precompile_headers(Hart-Engine
	PUBLIC
		
	PRIVATE 
		src/HartPch.hpp
)

target_compile_definitions(Hart-Engine
	PUBLIC

	PRIVATE
		HART_ENGINE
)

cmake_base_target_platform_definitions(Hart-Engine HART_ENGINE)
cmake_base_target_architecture_definitions(Hart-Engine HART_ENGINE)

# PLATFORM AND COMPILER SPECIFIC

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")

	target_compile_definitions(Hart-Engine
		PUBLIC

		PRIVATE
			NOMINMAX
			_CRT_SECURE_NO_WARNINGS
			WIN32_LEAN_AND_MEAN
	)

	if(MSVC)
		target_compile_options(Hart-Engine
			PUBLIC

			PRIVATE
				/Zc:__cplusplus
		)
	elseif(MINGW)
		target_link_libraries(Hart-Engine
			PUBLIC
				m
				OpenGL::GL
			PRIVATE

		)
		target_link_options(Hart-Engine
			PUBLIC

			PRIVATE
				-static-libgcc
				-static-libstdc++
		)
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(Hart-Engine
			PUBLIC
				OpenGL::GL
			PRIVATE
		)
		target_link_options(Hart-Engine
			PUBLIC

			PRIVATE
		)
	endif()

endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")

	if (TARGET OpenGL::OpenGL)
        target_link_libraries(Hart-Engine
			PUBLIC
				OpenGL::OpenGL
			PRIVATE
		)
    else()
        target_link_libraries(Hart-Engine
			PUBLIC
				OpenGL::GL
			PRIVATE

		)
    endif()

	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		target_link_libraries(Hart-Engine
			PUBLIC
				dl
				m
				pthread
			PRIVATE

		)
		target_link_options(Hart-Engine
			PUBLIC

			PRIVATE

		)
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(Hart-Engine
			PUBLIC

			PRIVATE
		)
		target_link_options(Hart-Engine
			PUBLIC

			PRIVATE
		)
	endif()

endif()

# CONFIGURATION SPECIFIC

target_compile_definitions(Hart-Engine
	PUBLIC

	PRIVATE
		$<$<CONFIG:Debug>:HART_ENGINE_DEBUG_BUILD>
		$<$<CONFIG:Debug>:DEBUG>

		$<$<CONFIG:Profile>:HART_ENGINE_PROFILE_BUILD>
		$<$<CONFIG:Profile>:NDEBUG>

		$<$<CONFIG:Release>:HART_ENGINE_RELEASE_BUILD>
		$<$<CONFIG:Release>:NDEBUG>
)