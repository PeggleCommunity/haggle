#pragma once

//Size: 625
namespace Sexy
{
	class PhysObj
	{
	public:
		static void setup();
		static bool check_exists();
		static float& mGravity;
		static constexpr float oGravity = 0.050000001f;
	};
};