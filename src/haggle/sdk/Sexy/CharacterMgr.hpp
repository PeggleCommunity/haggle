#pragma once

//Size: 152
namespace Sexy
{
	class CharacterMgr
	{
	public:
		static CharacterMgr* character_mgr;
		static void setup();
		static bool check_exists();
	};
};