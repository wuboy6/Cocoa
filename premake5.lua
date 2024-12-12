workspace "Cocoa"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Cocoa/vendor/GLFW/include"
IncludeDir["Glad"] = "Cocoa/vendor/Glad/include"
IncludeDir["Imgui"] = "Cocoa/vendor/imgui"
IncludeDir["glm"] = "Cocoa/vendor/glm"
IncludeDir["stb_image"] = "Cocoa/vendor/stb_image"

include "Cocoa/vendor/GLFW"
include "Cocoa/vendor/Glad"
include "Cocoa/vendor/imgui"

project "Cocoa"
	location "Cocoa"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "copch.h"
	pchsource "Cocoa/src/copch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"Imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CO_PLATEFORM_WINDOWS",
			"CO_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
	
		filter "configurations:Debug"
			defines "CO_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "CO_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "CO_DIST"
			runtime "Release"
			optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
	"%{prj.name}/src/**.h",
	"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Cocoa/vendor/spdlog/include",
		"Cocoa/src",
		"Cocoa/vendor",
		"%{IncludeDir.glm}"
	}
	
	links
	{
		"Cocoa"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CO_PLATEFORM_WINDOWS"
		}
	
		filter "configurations:Debug"
			defines "CO_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "CO_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "CO_DIST"
			runtime "Release"
			optimize "on"