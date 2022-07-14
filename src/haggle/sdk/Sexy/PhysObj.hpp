#pragma once

//Size: 625
namespace Sexy
{
	struct PhysObj_
	{
		char data[228];
	};

	class __declspec(dllexport) PhysObj
	{
	public:
		static void setup();
		static bool check_exists();
		static float& mGravity;
		static constexpr float oGravity = 0.050000001f;
	};
};
