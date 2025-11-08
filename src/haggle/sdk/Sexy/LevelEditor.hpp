#pragma once

#include "Board.hpp"

namespace Sexy
{
	class __declspec(dllexport) LevelEditor
	{
	public:
		static LevelEditor* levelEditor;

		static void setup();
		static bool check_exists();

        static void ShowLevelEditor(char p1, char p2);
	};
};
