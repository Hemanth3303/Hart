project "stb"
	kind "StaticLib"
	language "C"
	cdialect "C17"
	cppdialect "C++20"
	warnings "Off"
	targetdir("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")
	staticruntime "on"
	systemversion "latest"

	vpaths {
		["Header Files"] = { "**.h", "**.hpp" },
		["Source Files"] = { "**.c", "**.cpp" },
	}

	files { 
		"%{prj.location}/**.c",
		"%{prj.location}/**.h",
		"%{prj.location}/premake5.lua",
	}

	includedirs { 
		"%{prj.location}/include/"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		runtime "Release"
		optimize "On"

	filter { "system:windows" }
		defines { 
			"_CRT_SECURE_NO_WARNINGS", 
			"NOMINMAX", 
			"WIN32_LEAN_AND_MEAN"
		}
	filter { "system:windows", "action:vs*" }
		defines { 
			"STRICT",
			"_CRT_SECURE_NO_WARNINGS",
			"WIN32_LEAN_AND_MEAN",
		}