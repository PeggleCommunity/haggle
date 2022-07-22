#pragma once

#include "PlayerInfo.hpp"

namespace Sexy
{
	class __declspec(dllexport) StageMgr
	{
	public:
		static StageMgr* stage_mgr;
		static void setup();
		static bool check_exists();

		static int GetRandomLevel(Sexy::PlayerInfo* a2, int* a3, int* a4, bool a5, int a6);
		static int GetRandomLevel(Sexy::StageMgr* stage_mgr, Sexy::PlayerInfo* a2, int* a3, int* a4, bool a5, int a6);
	};
};
