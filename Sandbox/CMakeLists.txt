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

cmake_base_configure_target(Sandbox)
cmake_base_apply_target_definitions(Sandbox SANDBOX)
cmake_base_apply_target_definitions(Sandbox HART_CLIENT)
cmake_base_apply_os_definitions_to_target(Sandbox SANDBOX)
cmake_base_apply_architecture_definitions_to_target(Sandbox SANDBOX)
cmake_base_apply_compiler_definitions_to_target(Sandbox SANDBOX)
cmake_base_apply_sanitizers(Sandbox SANITIZERS ASAN UBSAN CONFIGS Debug)


# PLATFORM AND COMPILER SPECIFIC
if(MSVC)
	target_link_options(Sandbox PRIVATE
		"$<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS>"
		"$<$<CONFIG:Release>:/ENTRY:mainCRTStartup>"
	)
endif()

# POST-BUILD RESOURCE COPY
add_custom_command(
	TARGET Sandbox POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_SOURCE_DIR}/res"
		"$<TARGET_FILE_DIR:Sandbox>/res"
	COMMENT "Copying resource folder to binary directory"
)

# adding res to install
# cmake-base already handles bin, lib and include
# Note to future self:
# res/ means copy contents of res to bin/res
# if just res, then it will copy to bin/res/res
install(
	DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/res/"
    DESTINATION bin/res
)
