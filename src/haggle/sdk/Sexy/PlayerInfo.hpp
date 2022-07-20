#pragma once

namespace Sexy
{
	class __declspec(dllexport) PlayerInfo
	{
	public:
		static PlayerInfo* player_info;
		static void setup();
		static bool check_exists();
	};
};
