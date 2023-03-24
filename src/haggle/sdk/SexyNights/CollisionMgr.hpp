#pragma once

namespace SexyNights
{
	class __declspec(dllexport) CollisionMgr
	{
	public:
		static CollisionMgr* collision_mgr;
		static void setup();
		static bool check_exists();
	};
};
