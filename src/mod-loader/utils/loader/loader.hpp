#pragma once

#include <Windows.h>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <fstream>
#include <functional>

namespace loader
{
    void load(const char* bin_name);
	int run(int argc, char* argv[]);
}
