project "Hart-Engine"
	location "%{wks.location}/Hart-Engine"
	language "C++"
	cppdialect "C++20"
	cdialect "C17"
	targetdir("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
	objdir("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")
	staticruntime "Off"
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
		"%{prj.location}/Hart-Engine.lua",
		"%{wks.location}/premake5.lua",
	}

	includedirs {
		".",
		"%{prj.location}/src",
		"%{wks.location}/vendor/glfw/include",
		"%{wks.location}/vendor/glad/include",
		"%{wks.location}/vendor/stb_image/include",
	}

	links { "glfw", "glad", "stb_image" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		runtime "Release"
		optimize "On"

	filter "system:windows"
		links { "opengl32", "gdi32", "kernel32", "winmm", "shell32" }
		defines { 
			"HART_WINDOWS", 
			"NOMINMAX", 
			"WIN32_LEAN_AND_MEAN",
		}

	filter "system:linux"
		links { "pthread", "GL", "m", "dl", "rt", "X11" }
		defines "HART_LINUX"

	filter { "system:windows", "action:vs*" }
		defines { 
			"STRICT",
			"_CRT_SECURE_NO_WARNINGS",
			"WIN32_LEAN_AND_MEAN",
		}