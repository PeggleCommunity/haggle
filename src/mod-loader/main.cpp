#include "logger/logger.hpp"

std::initializer_list<std::string> ext_whitelist
{
	".dll",
	".asi",
};

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
	}
	else
	{
		std::vector<std::string> files;
		for (const auto& entry : std::filesystem::directory_iterator("./mods/"))
		{
			if (!entry.is_directory())
			{
				files.emplace_back(entry.path().string());
			}
		}

		PRINT_INFO("Loading Mods...");
		static int count = 0;
		for (const auto& bin : files)
		{
			for (const auto& ext : ext_whitelist)
			{
				if (ends_with(bin, ext))
				{
					LoadLibraryA(bin.c_str());
					PRINT_INFO("%s", bin.c_str());
					++count;
				}
			}
		}

		if (count == 1)
		{
			PRINT_INFO("1 mod loaded");
		}
		else if (count > 1)
		{
			PRINT_INFO("%d mods loaded", count);
		}
		else if (count <= 0)
		{
			PRINT_WARNING("No mods loaded");
		}

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
