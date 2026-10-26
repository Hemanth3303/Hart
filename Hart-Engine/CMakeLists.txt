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
		# this allows to use include glad and glfw in any order.
		# without this, glad must always be included before glfw
		GLFW_INCLUDE_NONE
)

cmake_base_configure_target(Hart-Engine)
cmake_base_apply_target_definitions(Hart-Engine HART_ENGINE)
cmake_base_apply_os_definitions_to_target(Hart-Engine HART_ENGINE)
cmake_base_apply_architecture_definitions_to_target(Hart-Engine HART_ENGINE)
cmake_base_apply_compiler_definitions_to_target(Hart-Engine HART_ENGINE)
cmake_base_apply_sanitizers(Hart-Engine SANITIZERS ASAN UBSAN CONFIGS Debug)

# PLATFORM AND COMPILER SPECIFIC
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	if(MINGW)
		target_link_libraries(Hart-Engine
			PUBLIC
				OpenGL::GL
		)
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(Hart-Engine
			PUBLIC
				OpenGL::GL
		)
	endif()

endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	if (TARGET OpenGL::OpenGL)
        target_link_libraries(Hart-Engine
			PUBLIC
				OpenGL::OpenGL
		)
    else()
        target_link_libraries(Hart-Engine
			PUBLIC
				OpenGL::GL
		)
    endif()
endif()
