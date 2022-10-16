project "glad"
	kind "StaticLib"
	language "C"
	cdialect "C17"
	cppdialect "C++20"
	location "%{wks.location}/vendor/glad"
	targetdir("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" ..outputdir.."/%{prj.name}" )
	staticruntime "Off"
	systemversion "latest"

	files { 
		"%{prj.location}/**.c",
		"%{prj.location}/**.h",
		"%{prj.location}/../glad.lua",
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