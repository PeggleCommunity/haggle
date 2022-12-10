#pragma once

namespace Sexy
{
	class __declspec(dllexport) Graphics
	{
	public:
		static Graphics* graphics;
		static void setup();

		int DrawImageF(Sexy::Graphics* input, int image, float x_pos, float y_pos);
	};
};
