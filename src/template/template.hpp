#pragma once

namespace Sexy
{
	class __declspec(dllexport) Template
	{
	public:
		static Template* temp;
		static void setup();
		static bool check_exists();
	};
};
