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

include "Hart-Engine/Hart-Engine.lua"
include "Sandbox/Sandbox.lua"
