#include "utils/logger/logger.hpp"
#include "utils/memory.hpp"
#include "utils/loader/loader.hpp"
#include <sstream>

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

	PRINT_INFO("In directory \"%s\"", std::filesystem::absolute(std::filesystem::path("./")).string().c_str());

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
					auto mod = LoadLibraryA(bin.c_str());

					if (GetLastError() != 0)
					{
						PRINT_ERROR("%s errored! (%i)", bin.c_str(), GetLastError());
					}
					else
					{
						PRINT_INFO("%s loaded!", bin.c_str());
						++count;
					}
				}
			}
		}

		if (count == 1)
		{
			PRINT_INFO("1 mod loaded");
		}
		else if (count > 1)
		{
			PRINT_INFO("%i mods loaded", count);
		}
		else if (count <= 0)
		{
			PRINT_WARNING("No mods loaded");
		}

		PRINT_INFO("Ready!");
	}
}

DWORD find_proc_id(const std::wstring& processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE) {
		return 0;
	}

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	return 0;
}

bool terminate_process(const std::wstring& processName)
{
	bool success = false;

	if (auto pid = find_proc_id(processName))
	{
		auto handle = OpenProcess(PROCESS_TERMINATE, false, pid);
		success = TerminateProcess(handle, 1);
		CloseHandle(handle);
	}

	return success;
}

int main(int argc, char* argv[])
{
	if (!std::filesystem::exists("./mods/"))
	{
		std::filesystem::create_directory("./mods/");
	}

	if (!std::filesystem::exists("./mods/cache.bin"))
	{
		if (terminate_process(L"Peggle.exe"))
		{
			if (terminate_process(L"popcapgame1.exe"))
			{
				std::filesystem::path cache = std::filesystem::absolute(std::filesystem::current_path() / "mods/cache.bin");
				std::filesystem::rename("C:/ProgramData/PopCap Games/Peggle/popcapgame1.exe", cache.c_str());
				ShellExecuteA(nullptr, "open", "Haggle.exe", 0, 0, SW_SHOWNORMAL);
				return 0;
			}
			else
			{
				MessageBoxA(nullptr, "Haggle was unable to extract the data necessary to run, please try again.", "Haggle Mod Loader", 0);
				return 0;
			}
		}
		else
		{
			auto resp = MessageBoxA(nullptr, "Since this is your first time launching Haggle, please launch Peggle through Steam first then launch Haggle.exe.\n\nPress retry to atempt automagic installation.\nPress cancel to stop the process and try again manually.", "Haggle Mod Loader", MB_RETRYCANCEL);

			if (resp == IDRETRY)
			{
				ShellExecuteA(0, "open", "steam://run/3480/", 0, 0, 0);
				while (!find_proc_id(L"Peggle.exe"))
				{
					Sleep(1000);
				}
				ShellExecuteA(nullptr, "open", "Haggle.exe", 0, 0, SW_SHOWNORMAL);
				return 0;
			}
			else if (resp == IDCANCEL)
			{
				return 0;
			}
		}
	}

	loader::load("./mods/cache.bin");
	init();
	return loader::run(argc, argv);
}
