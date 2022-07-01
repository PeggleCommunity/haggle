#pragma once

namespace Sexy
{
	class SoundMgr
	{
	public:
		static SoundMgr* sound_mgr;
		static void setup();
		static bool check_exists();

		static void AddSound(int a2, float a3 = 0.0f, int a4 = 0, int a5 = 1, int a6 = 1, float a7 = 1.0f);
		static int FadeMusic(int a2);
	};
};
