#pragma once

namespace Sexy
{
	struct LevelScreen_
	{
		char data[592];
	};

	class __declspec(dllexport) LevelScreen
	{
	public:
		static LevelScreen* level_screen;
		static void setup();
		static bool check_exists();

		static int DoPlay(int a3);
	};
};
