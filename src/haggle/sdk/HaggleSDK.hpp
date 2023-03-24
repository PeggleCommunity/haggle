#pragma once

class __declspec(dllexport) Haggle
{
public:
	enum class PeggleVersion : int
	{
		Unknown = -1,
		Deluxe101,
		NightsDeluxe10
	};

	static PeggleVersion version;
	static PeggleVersion get_game_version()
	{
		if (!std::strcmp(reinterpret_cast<char*>(0x005D675C), "Peggle Deluxe "))
		{
			return Haggle::PeggleVersion::Deluxe101;
		}
		else if (!std::strcmp(reinterpret_cast<char*>(0x006851D0), "Peggle Nights"))
		{
			return Haggle::PeggleVersion::NightsDeluxe10;
		}

		std::printf("[ HAGGLE ]: Unable to detect game!\n");
		return Haggle::PeggleVersion::Unknown;
	}
};
