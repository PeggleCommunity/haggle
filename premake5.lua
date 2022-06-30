workspace "Haggle"
	startproject "Haggle"
	location "./build/"
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
		"shadowedvariables",
		"undefinedidentifiers",
		"multiprocessorcompile",
	}

	platforms {
		"x86",
	}

	configurations {
		"Release",
		"Debug",
	}

	defines {
		"_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS",
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

	project "Haggle"
		targetname "haggle-sdk"
		language "c++"
		kind "staticlib"
		warnings "off"

		pchheader "stdafx.hpp"
		pchsource "./src/haggle/stdafx.cpp"
		forceincludes "stdafx.hpp"

		dependson {
			"MinHook",
		}

		links {
			"MinHook",
		}

		includedirs {
			"./src/haggle/",
			"./deps/minhook/include/",
		}

		files {
			"./src/haggle/**",
		}

	project "Example-Mod"
		targetname "example-mod"
		language "c++"
		kind "sharedlib"
		warnings "off"

		pchheader "stdafx.hpp"
		pchsource "./src/example-mod/stdafx.cpp"
		forceincludes "stdafx.hpp"

		dependson {
			"MinHook",
			"Haggle",
		}

		links {
			"MinHook",
			"Haggle",
		}

		includedirs {
			"./src/example-mod/",
			"./src/haggle/",
			"./deps/minhook/include/",
		}

		files {
			"./src/example-mod/**",
		}

	group "Example-Mod Dependencies"

	project "MinHook"
		targetname "MinHook"

		language "c++"
		kind "staticlib"

		files {
			"./deps/minhook/src/**",
		}

		includedirs {
			"./deps/minhook/include/",
		}
