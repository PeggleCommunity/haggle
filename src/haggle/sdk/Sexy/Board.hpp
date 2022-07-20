#pragma once

//Size: 592

namespace Sexy
{
	using KeyCode = unsigned int;

	class __declspec(dllexport) Board
	{
	public:
		static Board* board;

		static void setup();
		static bool check_exists();

		static void Reload();
		static void KeyDown(KeyCode keyCodePressed);
		static void SetSlowMo(bool a2, int a3);
		static int Reset();
	};
};
