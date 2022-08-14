#include "SoundMgr.hpp"

Sexy::SoundMgr* Sexy::SoundMgr::sound_mgr;

static char* (__fastcall* Sexy__SoundMgr__SoundMgr_)(Sexy::SoundMgr*, char*);
char* __fastcall Sexy__SoundMgr__SoundMgr(Sexy::SoundMgr* this_, char* edx)
{
	Sexy::SoundMgr::sound_mgr = this_;
	return Sexy__SoundMgr__SoundMgr_(this_, edx);
}

void Sexy::SoundMgr::setup()
{
	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			MH_CreateHook((void*)0x0045F1D0, Sexy__SoundMgr__SoundMgr, (void**)&Sexy__SoundMgr__SoundMgr_);
		} break;
	}
}

bool Sexy::SoundMgr::check_exists()
{
	if (Sexy::SoundMgr::sound_mgr == 0x0) return false;
	return true;
}

void Sexy::SoundMgr::AddSound(int a2, float a3, int a4, int a5, int a6, float a7)
{
	std::uint32_t address;

	switch (version)
	{
	case PeggleVersion::Deluxe101:
		address = 0x00458F30;
		break;

	case PeggleVersion::NightsDeluxe100:
		address = 0x00478A50;
		break;
	}

	if (!Sexy::SoundMgr::check_exists() || !address) return;
	reinterpret_cast<void(__thiscall*)(Sexy::SoundMgr*, int, float, int, int, int, float)>
		(address)(Sexy::SoundMgr::sound_mgr, a2, a3, a4, a5, a6, a7);
}

int Sexy::SoundMgr::FadeMusic(int a2)
{
	std::uint32_t address;

	switch (version)
	{
	case PeggleVersion::Deluxe101:
		address = 0x004375A0;
		break;
	}

	if (!Sexy::SoundMgr::check_exists() || !address) return 0;
	return reinterpret_cast<int(__thiscall*)(Sexy::SoundMgr*, int)>(address)(Sexy::SoundMgr::sound_mgr, a2);
}
