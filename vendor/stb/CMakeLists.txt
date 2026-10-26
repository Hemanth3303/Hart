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
)
target_include_directories(stb
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

cmake_base_configure_target(stb)
cmake_base_apply_target_definitions(stb STB)
cmake_base_apply_os_definitions_to_target(stb STB)
cmake_base_apply_architecture_definitions_to_target(stb STB)
cmake_base_apply_compiler_definitions_to_target(stb STB)

# Note to future self:
# include/ means copy contents of include/ to include/
# if just include, then it will copy to include/include
install(
	DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
	FILES_MATCHING
		PATTERN "*.h"
)
