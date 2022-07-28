#include "proxy.hpp"

EXPORT(DirectDrawCreate)
EXPORT(DirectDrawCreateEx)

std::unordered_map<const char*, HMODULE> proxy::libs;

FARPROC proxy::get(const char* lib, const char* func)
{
	if (!proxy::is_loaded(lib))
	{
		proxy::load(lib);
	}

	return GetProcAddress(proxy::libs[lib], func);
}

void proxy::load(const char* lib)
{
	char path[MAX_PATH];
	GetSystemDirectoryA(path, MAX_PATH);

	std::strcat(path, "\\");
	std::strcat(path, lib);

	proxy::libs[lib] = LoadLibraryA(path);
}

bool proxy::is_loaded(const char* lib)
{
	return proxy::libs.find(lib) != proxy::libs.end();
}
