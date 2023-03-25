outputdir = "%{cfg.system}-%{cfg.buildcfg}-%{cfg.architecture}"

workspace "Hart"
	configurations { "Debug", "Release", "Dist" }
	platforms { "x64" }
	startproject "Sandbox"

	filter "configurations:Debug"
		defines { "DEBUG", "HART_DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG", "HART_RELEASE" }
		optimize "On"

	filter "configurations:Dist"
		defines { "NDEBUG", "HART_DIST" }
		optimize "On"

	filter "platforms:x64"
		architecture "x86_64"

include "Sandbox/Sandbox.lua"
include "Hart-Engine/Hart-Engine.lua"
include "vendor/glfw.lua"
include "vendor/glad.lua"
include "vendor/stb_image.lua"

--when using the cmake generator module for premake
require "cmake"

newaction {
	trigger = "clean",
	description = "Remove all binaries, intermediates and build files",
	execute = function()
		print("Removing binaries")
		os.rmdir("./bin")
		os.rmdir("./build")
		os.rmdir("./distribution")
		os.rmdir("CMakeFiles")
		os.rmdir("Debug")
		os.rmdir("Release")
		os.rmdir("Dist")
		print("Removing intermediates")
		os.rmdir("./bin-int")
		os.rmdir("x86")
		os.rmdir("x64")
		print("Removing build files")
		os.rmdir("./.vs")
		os.remove("**.sln")
		os.remove("**.vcxproj.**")
		os.remove("**Makefile**")
		os.remove("**.workspace")
		os.remove("**.project")
		os.remove("CMakeLists.txt")
		os.remove("CMakeCache.txt")
		os.remove("vendor/glfw/glfw.cmake")
		os.remove("vendor/glad/glad.cmake")
		os.remove("vendor/stb_image/stb_image.cmake")
		os.remove("Hart-Engine/Hart-Engine.cmake")
		os.remove("Sandbox/Sandbox.cmake")
		print("Done")
	end
}