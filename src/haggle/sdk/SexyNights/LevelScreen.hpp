#pragma once

namespace SexyNights
{
	struct UnkStruct_
	{
		char data0[0x764];
		uint32_t stage;
		uint32_t level;
	};

	struct LevelScreen_
	{
		char data0[0x8C];
		UnkStruct_* unk;
		char data1[0x1C0];
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
