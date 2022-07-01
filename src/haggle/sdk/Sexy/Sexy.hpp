#pragma once

namespace Sexy
{
	//Sounds
	extern int& SOUND_PENALTY;
	extern int& SOUND_AAH;
	extern int& SOUND_COINSPIN_NO;
	extern int& SOUND_EXPLODE;

	//Images
	extern int& IMAGE_BALL;

	//Not the actual implementation, fix later!
	static std::string Format(const char* fmt, ...)
	{
		va_list va;
		va_start(va, fmt);
		char result[512]{};
		std::vsprintf(result, fmt, va);
		return std::string(result);
	}
}

static std::string MakeNextTurnString(const char* powerup_name, int turns, bool next)
{
	if (turns == 1)
	{
		return Sexy::Format("%s\nNext Turn", powerup_name);
	}
	else
	{
		if (next)
		{
			return Sexy::Format("%s\nNext %i Turns", powerup_name, turns);
		}
		else
		{
			return Sexy::Format("%s\n%i Turns", powerup_name, turns);
		}
	}
}
