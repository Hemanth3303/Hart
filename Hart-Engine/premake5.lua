project "Hart-Engine"
	location "%{wks.location}/Hart-Engine"
	language "C++"
	cppdialect "C++20"
	cdialect "C17"
	targetdir("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
	objdir("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")
	staticruntime "Off"
	systemversion "latest"
	targetname "%{prj.name}"
	kind "StaticLib"

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
	}

	includedirs {
		"%{prj.location}/src",
		"."
	}

	--links { "" }

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
		links { "opengl32", "gdi32", "kernel32", "winmm" }
		defines "HART_WINDOWS"

	filter "system: linux"
		links {"pthread", "GL", "m", "dl", "rt", "X11"}
		defines "HART_LINUX"

	filter { "system:windows", "action:vs*" }
		defines { "_CRT_SECURE_NO_WARNINGS" }