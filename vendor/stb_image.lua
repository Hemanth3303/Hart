project "stb_image"
	kind "StaticLib"
	language "C"
	cdialect "C17"
	cppdialect "C++20"
	location "%{wks.location}/vendor/stb_image"
	targetdir("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")
	staticruntime "Off"
	systemversion "latest"

	files { 
		"%{prj.location}/**.c",
		"%{prj.location}/**.h",
		"%{prj.location}/../stb_image.lua",
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