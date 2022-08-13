#pragma once

#include <cstdint>
#include <cmath>
#include <string>

#include <Windows.h>
#include <DbgHelp.h>

//Deps
#include "MinHook.h"

//IDA Defs
#include "utils/defs.h"

enum class PeggleVersion : int
{
	Unknown = -1,
	Deluxe101,  // Steam and EA Play/Origin
	NightsDeluxe100,  // Steam
	NightsDeluxe101  // EA Play/Origin
};

extern PeggleVersion version;
