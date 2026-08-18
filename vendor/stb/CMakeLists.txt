add_library(stb STATIC
	"src/stb_image.c"
	"include/stb_image.h"
	"src/stb_truetype.c"
	"include/stb_truetype.h"
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

target_include_directories(stb
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE

)

target_compile_definitions(stb
	PUBLIC

	PRIVATE
		STB
)

cmake_base_target_platform_definitions(stb STB)
cmake_base_target_architecture_definitions(stb STB)

# PLATFORM AND COMPILER SPECIFIC

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")

	target_compile_definitions(stb
		PUBLIC

		PRIVATE
			NOMINMAX
			_CRT_SECURE_NO_WARNINGS
			WIN32_LEAN_AND_MEAN
	)

	if(MSVC)
		target_compile_options(stb
			PUBLIC

			PRIVATE
				/Zc:__cplusplus
				/Zc:preprocessor
		)
	elseif(MINGW)
		target_link_libraries(stb
			PUBLIC
				m
			PRIVATE

		)
		target_link_options(stb
			PUBLIC

			PRIVATE
				-static-libgcc
				-static-libstdc++
		)
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(stb
			PUBLIC

			PRIVATE
		)
		target_link_options(stb
			PUBLIC

			PRIVATE
		)
	endif()

endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")

	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		target_link_libraries(stb
			PUBLIC
				dl
				m
				pthread
			PRIVATE

		)
		target_link_options(stb
			PUBLIC

			PRIVATE

		)
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(stb
			PUBLIC

			PRIVATE
		)
		target_link_options(stb
			PUBLIC

			PRIVATE
		)
	endif()

endif()

# CONFIGURATION SPECIFIC

target_compile_definitions(stb
	PUBLIC

	PRIVATE
		$<$<CONFIG:Debug>:STB_DEBUG_BUILD>
		$<$<CONFIG:Debug>:DEBUG>

		$<$<CONFIG:Profile>:STB_PROFILE_BUILD>
		$<$<CONFIG:Profile>:NDEBUG>

		$<$<CONFIG:Release>:STB_RELEASE_BUILD>
		$<$<CONFIG:Release>:NDEBUG>
)
