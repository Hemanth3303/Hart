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
	}

	includedirs {
		"%{prj.location}/src",
		"%{wks.location}/Hart-Engine/src"
	}

	links { "Hart-Engine" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		kind "ConsoleApp"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		kind "ConsoleApp"

	filter "configurations:Dist"
		runtime "Release"
		optimize "On"
		kind "WindowedApp"
		entrypoint "mainCRTStartup"

	filter { "system:windows", "action:vs*" }
		defines { "_CRT_SECURE_NO_WARNINGS" }
