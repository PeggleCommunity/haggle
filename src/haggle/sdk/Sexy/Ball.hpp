#pragma once


//Size: 400
namespace Sexy
{
	class __declspec(dllexport) Ball
	{
	public:
		static Ball* ball;

		static void setup();
		static bool check_exists();


		static void SetPos(float a2, float a3);
	};
};
