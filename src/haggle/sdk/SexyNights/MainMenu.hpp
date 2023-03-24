#pragma once

namespace SexyNights
{
	struct MainMenu_
	{
		char data[244];
	};

	class __declspec(dllexport) MainMenu
	{
	public:
		static MainMenu* main_menu;
		static void setup();
		static bool check_exists();

		static void StartGame();
	};
};
