#pragma once

namespace Sexy
{
	//Not the exact size, size unknown
	struct FloatingText_
	{
		char padding_0[96];
		uint32_t color;
		int unk_0;
		int unk_1;
		int unk_2;
		int unk_3;
		int unk_4;
		int unk_5;
		char padding_2[12];
		int unk_9;
		float float_offset_start;
		char padding_3[156];
	};


	class __declspec(dllexport) FloatingText
	{
	public:
		static FloatingText* floating_text;
		static void setup();
		static bool check_exists();
	};
};
