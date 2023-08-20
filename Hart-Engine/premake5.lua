project "Hart-Engine"
	language "C++"
	cppdialect "C++20"
	cdialect "C17"
	targetdir("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
	objdir("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")
	staticruntime "on"
	kind "StaticLib"
	systemversion "latest"
	targetname "%{prj.name}"

	defines {
		"HART_ENGINE",
	}

	filter { "action:not cmake" }
		pchheader "HartPch.hpp"
		pchsource "%{prj.location}/src/HartPch.cpp"

	filter {  }

	vpaths {
		["Header Files"] = { "**.h", "**.hpp" },
		["Source Files"] = { "**.c", "**.cpp" },
	}

	files {
		"%{prj.location}/src/**.c",
		"%{prj.location}/src/**.cpp",
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.hpp",
		"%{prj.location}/**.glsl",
		"%{prj.location}/**.vert",
		"%{prj.location}/**.frag",
		"%{prj.location}/premake5.lua",
		"%{wks.location}/premake5.lua",
	}

	includedirs {
		".",
		"%{prj.location}/src",
		"%{prj.location}/../vendor/glfw/include",
		"%{prj.location}/../vendor/glad/include",
		"%{prj.location}/../vendor/stb/include",
	}

	-- remember to add dependencies to Client App/Game's links{} section if compiler!=MSVC (action: not vs*)
	links { "glfw", "glad", "stb" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		defines {
			"HART_DEBUG"
		}

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		defines {
			"HART_RELEASE"
		}

	filter "configurations:Dist"
		runtime "Release"
		optimize "On"
		defines {
			"HART_DIST"
		}

	filter { "system:windows", "action:not vs*" }
		links { "opengl32", "gdi32", "kernel32", "winmm", "shell32", "user32" }
		defines { 
			"HART_WINDOWS", 
			"NOMINMAX", 
			"_CRT_SECURE_NO_WARNINGS",
			"WIN32_LEAN_AND_MEAN",
		}

	filter "system:linux"
		links { "pthread", "GL", "m", "dl", "rt", "X11" }
		defines "HART_LINUX"

	filter { "system:windows", "action:vs*" }
		defines { 
			"HART_WINDOWS", 
			"NOMINMAX", 
			"STRICT",
			"_CRT_SECURE_NO_WARNINGS",
			"WIN32_LEAN_AND_MEAN",
		}