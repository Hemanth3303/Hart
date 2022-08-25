outputdir = "%{cfg.system}-%{cfg.buildcfg}-%{cfg.architecture}"

workspace "Hart"
	configurations { "Debug", "Release", "Dist" }
	platforms { "x64" }
	startproject "Sandbox"

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

	filter "configurations:Dist"
		defines { "NDEBUG" }
		optimize "On"

	filter "platforms:x64"
		architecture "x86_64"

include "Hart-Engine"
include "Sandbox"


newaction {
	trigger = "clean",
	description = "Remove all binaries, intermediates and build files",
	execute=function()
		print("Removing binaries")
		os.rmdir("./bin")
		print("Removing intermediates")
		os.rmdir("./bin-int")
		print("Removing build files")
		os.rmdir("./.vs")
		os.remove("**.sln")
		os.remove("**.vcxproj.**")
		os.remove("**Makefile**")
		os.remove("**.workspace")
		os.remove("**.project")
		print("Done")
	end
}
