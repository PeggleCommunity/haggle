#include "Sexy.hpp"

//Sounds
int& Sexy::Assets::SOUND_PENALTY = *reinterpret_cast<int*>(0x006502E4);
int& Sexy::Assets::SOUND_AAH = *reinterpret_cast<int*>(0x00650218);
int& Sexy::Assets::SOUND_COINSPIN_NO = *reinterpret_cast<int*>(0x006500FC);
int& Sexy::Assets::SOUND_EXPLODE = *reinterpret_cast<int*>(0x006502A4);
int& Sexy::Assets::SOUND_POWERUP_GUIDE = *reinterpret_cast<int*>(0x00650104);

//Images
int& Sexy::Assets::IMAGE_BALL = *reinterpret_cast<int*>(0x0065023C);

int Sexy::Assets::get(Asset asset)
{
	switch(asset)
	{
		//Sounds
	case Asset::SOUND_AAH:
		return Sexy::Assets::SOUND_AAH;
		break;

	case Asset::SOUND_PENALTY:
		return Sexy::Assets::SOUND_PENALTY;
		break;

	case Asset::SOUND_COINSPIN_NO:
		return Sexy::Assets::SOUND_COINSPIN_NO;
		break;

	case Asset::SOUND_EXPLODE:
		return Sexy::Assets::SOUND_EXPLODE;
		break;

	case Asset::SOUND_POWERUP_GUIDE:
		return Sexy::Assets::SOUND_POWERUP_GUIDE;
		break;

		//Images
	case Asset::IMAGE_BALL:
		return Sexy::Assets::IMAGE_BALL;
		break;
	}
}
