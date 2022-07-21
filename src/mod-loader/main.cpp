#include "logger/logger.hpp"
#include <sstream>

std::initializer_list<std::string> ext_whitelist
{
	".dll",
	".asi",
};

std::vector<std::pair<HMODULE, std::string>> loaded;

bool ends_with(std::string const& value, std::string const& ending)
{
	if (ending.size() > value.size()) return false;
	return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

void init()
{
	logger::init("Haggle Mod Loader");
	std::printf("----- Haggle Mod Loader -----\n");

	if (!std::filesystem::exists("./mods/"))
	{
		PRINT_ERROR("No mods folder found!");
		PRINT_INFO("Make a mods folder in your Peggle directory");
		PRINT_INFO("Peggle Directory: %s", std::filesystem::absolute(std::filesystem::path("./")).string().c_str());
	}
	else
	{
		std::filesystem::path orig_path = std::filesystem::current_path();
		std::filesystem::current_path("./mods/");

		std::vector<std::string> files;
		for (const auto& entry : std::filesystem::directory_iterator("./"))
		{
			if (!entry.is_directory())
			{
				files.emplace_back(entry.path().string());
			}
		}

		PRINT_INFO("Loading Mods...");
		for (const auto& bin : files)
		{
			for (const auto& ext : ext_whitelist)
			{
				if (ends_with(bin, ext))
				{
					auto handle = LoadLibraryA(bin.c_str());

					if (GetLastError() != 0)
					{
						PRINT_ERROR("%s errored! (%i)", bin.c_str(), GetLastError());
					}
					else
					{
						//If using the new haggle version function
						std::string version_string = "v%i.%i.%i";

						int major = 0;
						int minor = 0;
						int patch = 0;

						/*
						auto major_proc = GetProcAddress(handle, "haggle_major_version");
						auto minor_proc = GetProcAddress(handle, "haggle_minor_version");
						auto patch_proc = GetProcAddress(handle, "haggle_patch_version");

						if (major_proc && minor_proc && patch_proc)
						{
							major = ((int(*)(void))major_proc)();
							minor = ((int(*)(void))minor_proc)();
							patch = ((int(*)(void))patch_proc)();
						}
						*/

						version_string = logger::va(version_string.c_str(), major, minor, patch);

						PRINT_INFO("%s loaded! (%s)", bin.c_str(), version_string.c_str());
						loaded.emplace_back(handle, bin);
					}
				}
			}
		}

		std::filesystem::current_path(orig_path);

		if (loaded.size() >= 1)
		{
			PRINT_INFO("%i mods loaded", loaded.size());
		}
		else if (loaded.size() <= 0)
		{
			PRINT_WARNING("No mods loaded");
		}

		/*
		for (auto dll : loaded)
		{
			//If using the new haggle init method
			auto init_proc = GetProcAddress(dll.first, "haggle_initalize");
			if (init_proc) ((void(*)(void))init_proc)();
			else PRINT_WARNING("No initalize import for %s", dll.second.c_str());
		}
		*/

		files.clear();
		loaded.clear();

		PRINT_INFO("Ready!");
	}
}

DWORD WINAPI OnAttachImpl(LPVOID lpParameter)
{
	init();
	return 0;
}

DWORD WINAPI OnAttach(LPVOID lpParameter)
{
	__try
	{
		return OnAttachImpl(lpParameter);
	}
	__except (0)
	{
		FreeLibraryAndExitThread((HMODULE)lpParameter, 0xDECEA5ED);
	}

	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, 0, OnAttach, hModule, 0, nullptr);
		return true;
	}

	return false;
}
