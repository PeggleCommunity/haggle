#pragma once

namespace SexyNights
{
	enum class Asset : int
	{
		SOUND_PENALTY,
		SOUND_AAH,
		SOUND_COINSPIN_NO,
		SOUND_EXPLODE,
		SOUND_POWERUP_GUIDE,

		IMAGE_BALL,
	};

	class __declspec(dllexport) Assets final
	{
	public:
		static int get(Asset asset);
	};

	//Not the actual implementation, fix later!
	static std::string Format(const char* fmt, ...)
	{
		va_list va;
		va_start(va, fmt);
		char result[512]{};
		std::vsprintf(result, fmt, va);
		return std::string(result);
	}

	static std::string MakeNextTurnString(const char* powerup_name, int turns, bool next)
	{
		if (turns == 1)
		{
			return SexyNights::Format("%s\nNext Turn", powerup_name);
		}
		else
		{
			if (next)
			{
				return SexyNights::Format("%s\nNext %i Turns", powerup_name, turns);
			}
			else
			{
				return SexyNights::Format("%s\n%i Turns", powerup_name, turns);
			}
		}
	}
}
