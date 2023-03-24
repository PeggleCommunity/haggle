#pragma once


//Size: 400
namespace SexyNights
{
	class __declspec(dllexport) Ball
	{
	public:
		static Ball* ball;

		static void setup();
		static bool check_exists();


		static void SetPos(float x_pos, float y_pos);
		static void SetVelocity(float x_velo, float y_velo);
	};
};
