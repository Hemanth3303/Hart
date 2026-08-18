add_library(miniaudio STATIC
	"src/miniaudio.c"
	"include/miniaudio.h"
)


set_target_properties(miniaudio PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
	C_STANDARD 17
	C_STANDARD_REQUIRED ON
	C_EXTENSIONS OFF
	POSITION_INDEPENDENT_CODE ON
	OUTPUT_NAME miniaudio
)

target_include_directories(miniaudio
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE

)

target_compile_definitions(miniaudio
	PUBLIC

	PRIVATE
		MINIAUDIO
)

cmake_base_target_platform_definitions(miniaudio MINIAUDIO)
cmake_base_target_architecture_definitions(miniaudio MINIAUDIO)

# PLATFORM AND COMPILER SPECIFIC

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")

	target_compile_definitions(miniaudio
		PUBLIC

		PRIVATE
			NOMINMAX
			_CRT_SECURE_NO_WARNINGS
			WIN32_LEAN_AND_MEAN
	)

	if(MSVC)
		target_compile_options(miniaudio
			PUBLIC

			PRIVATE
				/Zc:__cplusplus
				/Zc:preprocessor
		)
	elseif(MINGW)
		target_link_libraries(miniaudio
			PUBLIC
				m
			PRIVATE

		)
		target_link_options(miniaudio
			PUBLIC

			PRIVATE
				-static-libgcc
				-static-libstdc++
		)
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(miniaudio
			PUBLIC

			PRIVATE
		)
		target_link_options(miniaudio
			PUBLIC

			PRIVATE
		)
	endif()

endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")

	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		target_link_libraries(miniaudio
			PUBLIC
				dl
				m
				pthread
			PRIVATE

		)
		target_link_options(miniaudio
			PUBLIC

			PRIVATE

		)
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(miniaudio
			PUBLIC

			PRIVATE
		)
		target_link_options(miniaudio
			PUBLIC

			PRIVATE
		)
	endif()

endif()

# CONFIGURATION SPECIFIC

target_compile_definitions(miniaudio
	PUBLIC

	PRIVATE
		$<$<CONFIG:Debug>:MINIAUDIO_DEBUG_BUILD>
		$<$<CONFIG:Debug>:DEBUG>

		$<$<CONFIG:Profile>:MINIAUDIO_PROFILE_BUILD>
		$<$<CONFIG:Profile>:NDEBUG>

		$<$<CONFIG:Release>:MINIAUDIO_RELEASE_BUILD>
		$<$<CONFIG:Release>:NDEBUG>
)
