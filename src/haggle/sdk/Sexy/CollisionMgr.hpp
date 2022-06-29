#pragma once

namespace Sexy
{
	class CollisionMgr
	{
	public:
		static CollisionMgr* collision_mgr;
		static void setup();
		static bool check_exists();
	};
};