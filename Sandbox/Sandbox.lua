project "Sandbox"
	location "%{wks.location}/Sandbox"
	language "C++"
	cppdialect "C++20"
	cdialect "C17"
	targetdir("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
	objdir("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")
	staticruntime "on"
	systemversion "latest"
	targetname "%{prj.name}"

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
		"%{prj.location}/**.png",
		"%{prj.location}/**.jpg",
		"%{prj.location}/**.jpeg",
		"%{prj.location}/Sandbox.lua",
	}

	includedirs {
		"%{prj.location}/src",
		"%{wks.location}/Hart-Engine/src",
		"%{wks.location}/vendor/glfw/include",
		"%{wks.location}/vendor/glad/include",
		"%{wks.location}/vendor/stb/include",
	}

	links { "Hart-Engine" }

	filter "configurations:Debug*"
		runtime "Debug"
		symbols "On"
		kind "ConsoleApp"

	filter "configurations:Release*"
		runtime "Release"
		optimize "On"
		kind "ConsoleApp"

	filter "configurations:Dist*"
		runtime "Release"
		optimize "On"
		kind "WindowedApp"
		entrypoint "mainCRTStartup"

	filter { "system:windows" }
		defines { 
			"_CRT_SECURE_NO_WARNINGS", 
			"NOMINMAX", 
			"WIN32_LEAN_AND_MEAN"
		}
		postbuildcommands {
			"xcopy %{prj.location}\\res %{wks.location}\\bin\\" ..outputdir.. "\\%{prj.name}\\res /E /H /C /I /Y"
		}

	filter { "system:windows", "action:not vs*" }
		links { "glfw", "glad", "stb" }
		links { "opengl32", "gdi32", "kernel32", "winmm", "shell32", "user32" }

	filter { "system:linux" }
		links { "glfw", "glad", "stb" }
		links { "pthread", "GL", "m", "dl", "rt", "X11" }

	filter { "system:windows", "action:vs*" }
		defines { 
			"STRICT",
			"_CRT_SECURE_NO_WARNINGS",
			"WIN32_LEAN_AND_MEAN",
		}