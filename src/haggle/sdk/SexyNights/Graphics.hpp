#pragma once

namespace SexyNights
{
	class __declspec(dllexport) Graphics
	{
	public:
		static Graphics* graphics;
		static void setup();

		int DrawImageF(SexyNights::Graphics* input, int image, float x_pos, float y_pos);
	};
};
