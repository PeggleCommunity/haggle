#pragma once

namespace Sexy
{
	class Template
	{
	public:
		static Template* temp;
		static void setup();
		static bool check_exists();
	};
};