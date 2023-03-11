project "Sandbox"
	location "%{wks.location}/Sandbox"
	language "C++"
	cppdialect "C++20"
	cdialect "C17"
	targetdir("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
	objdir("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")
	staticruntime "Off"
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
		defines { "_CRT_SECURE_NO_WARNINGS", "NOMINMAX", "WIN32_LEAN_AND_MEAN" }

	filter { "system:windows", "action:not vs" }
		links { "glfw", "glad", "opengl32", "gdi32", "kernel32", "winmm", "shell32" }

	filter { "system:linux" }
		links { "glfw", "glad", "pthread", "GL", "m", "dl", "rt", "X11" }
