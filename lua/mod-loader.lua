workspace "Mod Loader"
	startproject "mod-loader"
	location "../build/"
	targetdir "%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.platform}/"
	objdir "%{wks.location}/obj/%{prj.name}/%{cfg.buildcfg}-%{cfg.platform}/"
	buildlog "%{wks.location}/obj/%{cfg.platform}/%{cfg.buildcfg}-%{prj.name}.log"

	largeaddressaware "on"
	editandcontinue "off"
	staticruntime "on"

	systemversion "latest"
	characterset "unicode"
	warnings "extra"

	flags {
		"noincrementallink",
		"no64bitchecks",
		"shadowedvariables",
		"undefinedidentifiers",
		"multiprocessorcompile",
	}

	defines {
		"NOMINMAX",
		"WIN32_LEAN_AND_MEAN",
		"_CRT_SECURE_NO_WARNINGS",
		"_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS",
	}

	platforms {
		"x86",
	}

	configurations {
		"Release",
		"Debug",
	}

	--x86
	filter "platforms:x86"	
		architecture "x86"
	--end

	filter "Release"
		defines "NDEBUG"
		optimize "full"
		runtime "release"
		symbols "off"

	filter "Debug"
		defines "DEBUG"
		optimize "debug"
		runtime "debug"
		symbols "on"

project "Mod Loader"
		targetname "Haggle"
		language "c++"
		cppdialect "c++17"
		kind "consoleapp"
		warnings "off"

		pchheader "stdafx.hpp"
		pchsource "../src/mod-loader/stdafx.cpp"
		forceincludes "stdafx.hpp"

		includedirs {
			"../src/mod-loader/",
		}

		files {
			"../src/mod-loader/**",
		}

		linkoptions {
			"/NXCOMPAT:NO",
			"/IGNORE:4254",
			"/DYNAMICBASE:NO",
			"/SAFESEH:NO",
			"/LARGEADDRESSAWARE",
			"/LAST:.main",
		}
