#include "Sexy.hpp"

int Sexy::Assets::get(Asset asset)
{
	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			switch (asset)
			{
				//Sounds
				case Asset::SOUND_AAH:
				{
					return *reinterpret_cast<int*>(0x00650218);
				} break;

				case Asset::SOUND_PENALTY:
				{
					return  *reinterpret_cast<int*>(0x006502E4);
				} break;

				case Asset::SOUND_COINSPIN_NO:
				{
					return *reinterpret_cast<int*>(0x006500FC);
				} break;

				case Asset::SOUND_EXPLODE:
				{
					return *reinterpret_cast<int*>(0x006502A4);
				} break;

				case Asset::SOUND_POWERUP_GUIDE:
				{
					return *reinterpret_cast<int*>(0x00650104);
				} break;

				//Images
				case Asset::IMAGE_BALL:
				{
					return *reinterpret_cast<int*>(0x0065023C);
				} break;

			} break;

		} break;

		case PeggleVersion::NightsDeluxe100:
		{

		} break;
	}

	return 0;
}
