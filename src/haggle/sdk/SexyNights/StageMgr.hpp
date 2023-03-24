#pragma once

#include "PlayerInfo.hpp"

namespace SexyNights
{
	class __declspec(dllexport) StageMgr
	{
	public:
		static StageMgr* stage_mgr;
		static void setup();
		static bool check_exists();

		static int GetRandomLevel(SexyNights::PlayerInfo* a2, int* a3, int* a4, bool a5, int a6);
		static int GetRandomLevel(SexyNights::StageMgr* stage_mgr, SexyNights::PlayerInfo* a2, int* a3, int* a4, bool a5, int a6);
	};
};
