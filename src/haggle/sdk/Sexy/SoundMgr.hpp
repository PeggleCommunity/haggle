#pragma once

namespace Sexy
{
	class SoundMgr
	{
	public:
		static SoundMgr* sound_mgr;
		static void setup();
		static bool check_exists();

		static void AddSound(int a2, float a3, int a4, int a5, int a6, float a7);
		static int FadeMusic(int a2);
	};
};