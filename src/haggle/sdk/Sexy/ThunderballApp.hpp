#pragma once

//Size: 625
namespace Sexy
{
	class __declspec(dllexport) ThunderballApp
	{
	public:
		static ThunderballApp* thunderball;

		static void setup();
		static bool check_exists();

		static void DoToMenu();
		static int ShowLevelScreen(bool a2);
		static int ShowBoard(bool a2, bool a3);
	};
};
