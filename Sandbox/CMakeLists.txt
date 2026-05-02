file(GLOB_RECURSE SANDBOX_SRC CONFIGURE_DEPENDS "*.h" "*.c" "*.hpp" "*.cpp")

add_executable(Sandbox
	${SANDBOX_SRC}
)

set_target_properties(Sandbox PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
	C_STANDARD 17
	C_STANDARD_REQUIRED ON
	C_EXTENSIONS OFF
	OUTPUT_NAME Sandbox
)

target_include_directories(Sandbox
	PUBLIC

	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CMAKE_SOURCE_DIR}/Hart-Engine/src
		${CMAKE_SOURCE_DIR}/vendor/glad/include
		${CMAKE_SOURCE_DIR}/vendor/glfw/include
		${CMAKE_SOURCE_DIR}/vendor/miniaudio/include
		${CMAKE_SOURCE_DIR}/vendor/stb/include
)

target_link_libraries(Sandbox
	PUBLIC

	PRIVATE
		Hart-Engine
)

target_compile_definitions(Sandbox
	PUBLIC

	PRIVATE
		SANDBOX
		HART_CLIENT
)

cmake_base_target_platform_definitions(Sandbox SANDBOX)
cmake_base_target_architecture_definitions(Sandbox SANDBOX)

# PLATFORM AND COMPILER SPECIFIC

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")

	target_compile_definitions(Sandbox
		PUBLIC

		PRIVATE
			NOMINMAX
			_CRT_SECURE_NO_WARNINGS
			WIN32_LEAN_AND_MEAN
	)

	if(MSVC)
		target_compile_options(Sandbox
			PUBLIC

			PRIVATE
				/Zc:__cplusplus
		)
	elseif(MINGW)
		target_link_libraries(Sandbox
			PUBLIC
				m
			PRIVATE
		)
		target_link_options(Sandbox
			PUBLIC

			PRIVATE
				-static
				-static-libgcc
				-static-libstdc++
		)
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(Sandbox
			PUBLIC

			PRIVATE
		)
		target_link_options(Sandbox
			PUBLIC

			PRIVATE
				-static
				-static-libstdc++
		)
	endif()

endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")

	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		target_link_libraries(Sandbox
			PUBLIC
				dl
				m
				pthread
			PRIVATE

		)
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(Sandbox
			PUBLIC

			PRIVATE
		)
		target_link_options(Sandbox
			PUBLIC

			PRIVATE

		)
	endif()

endif()

if(MSVC)
	target_link_options(Sandbox PRIVATE
		"$<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS>"
		"$<$<CONFIG:Release>:/ENTRY:mainCRTStartup>"
	)
endif()

# CONFIGURATION SPECIFIC

target_compile_definitions(Sandbox
	PUBLIC

	PRIVATE
		$<$<CONFIG:Debug>:SANDBOX_DEBUG_BUILD>
		$<$<CONFIG:Debug>:HART_CLIENT_DEBUG_BUILD>
		$<$<CONFIG:Debug>:DEBUG>

		$<$<CONFIG:Profile>:SANDBOX_PROFILE_BUILD>
		$<$<CONFIG:Profile>:HART_CLIENT_PROFILE_BUILD>
		$<$<CONFIG:Profile>:NDEBUG>

		$<$<CONFIG:Release>:SANDBOX_RELEASE_BUILD>
		$<$<CONFIG:Release>:HART_CLIENT_RELEASE_BUILD>
		$<$<CONFIG:Release>:NDEBUG>
)

# POST-BUILD RESOURCE COPY

add_custom_command(
	TARGET Sandbox POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_SOURCE_DIR}/res"
		"$<TARGET_FILE_DIR:Sandbox>/res"
	COMMENT "Copying resource folder to binary directory"
)