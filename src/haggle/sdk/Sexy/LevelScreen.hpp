#pragma once

namespace Sexy
{
	class LevelScreen
	{
	public:
		static LevelScreen* level_screen;
		static void setup();
		static bool check_exists();
	};
};
