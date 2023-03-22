#pragma once

#include <iostream>
#include <cstdio>
#include <algorithm>

#define PRINT_FILE_CONSOLE(__FMT__, ...)												\
	if (logger::file)									\
	{																					\
		std::fprintf(logger::file, __FMT__, __VA_ARGS__);										\
		std::fflush(logger::file);																\
	}																					\
																						\
	std::printf(__FMT__, __VA_ARGS__)

#ifdef DEBUG
#define PRINT_DEBUG(__FMT__, ...)													\
		PRINT_FILE_CONSOLE("[ DEBUG ][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__)

#define PRINT_INFO(__FMT__, ...)													\
		PRINT_FILE_CONSOLE("[ INFO ][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__)

#define PRINT_WARNING(__FMT__, ...)													\
		PRINT_FILE_CONSOLE("[ WARNING ][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__)

#define PRINT_ERROR(__FMT__, ...)													\
		PRINT_FILE_CONSOLE("[ ERROR ][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__)
#else
#define PRINT_DEBUG(__FMT__, ...)

#define PRINT_INFO(__FMT__, ...)													\
		PRINT_FILE_CONSOLE("[ INFO ]: " __FMT__ "\n", __VA_ARGS__)

#define PRINT_WARNING(__FMT__, ...)													\
		PRINT_FILE_CONSOLE("[ WARNING ]: " __FMT__ "\n", __VA_ARGS__)

#define PRINT_ERROR(__FMT__, ...)													\
		PRINT_FILE_CONSOLE("[ ERROR ]: " __FMT__ "\n", __VA_ARGS__)
#endif

class logger
{
public:
	static _iobuf* file;

	static void init(const char* title)
	{
		if (GetConsoleWindow() == NULL)
		{
			std::ios_base::sync_with_stdio(false);

			file = std::fopen("mods/haggle-console.log", "wb");

			AllocConsole();
			SetConsoleTitleA(title);

			std::freopen("CONOUT$", "w", stdout);
			std::freopen("CONIN$", "r", stdin);
		}
	}

	static std::string va(const char* fmt, ...)
	{
		va_list va;
		va_start(va, fmt);
		char result[512]{};
		std::vsprintf(result, fmt, va);
		return std::string(result);
	}
};
