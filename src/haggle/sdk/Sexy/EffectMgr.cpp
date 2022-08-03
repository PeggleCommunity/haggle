#include "EffectMgr.hpp"

Sexy::EffectMgr* Sexy::EffectMgr::effect_mgr;

static char* (__fastcall* Sexy__EffectMgr__EffectMgr_)(Sexy::EffectMgr*, char*);
char* __fastcall Sexy__EffectMgr__EffectMgr(Sexy::EffectMgr* this_, char* edx)
{
	Sexy::EffectMgr::effect_mgr = this_;
	return Sexy__EffectMgr__EffectMgr_(this_, edx);
}

void Sexy::EffectMgr::setup()
{
	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			MH_CreateHook((void*)0x004471E0, Sexy__EffectMgr__EffectMgr, (void**)&Sexy__EffectMgr__EffectMgr_);
		} break;
	}
}

bool Sexy::EffectMgr::check_exists()
{
	if (Sexy::EffectMgr::effect_mgr == 0x0) return false;
	return true;
}

void Sexy::EffectMgr::AddPyramid(float a2, float a3)
{
	std::uint32_t address;

	switch (version)
	{
	case PeggleVersion::Deluxe101:
		address = 0x00450C60;
		break;
	}

	if (!Sexy::EffectMgr::check_exists()) return;
	reinterpret_cast<void(__thiscall*)(Sexy::EffectMgr*, float, float)>(address)(Sexy::EffectMgr::effect_mgr, a2, a3);
}
