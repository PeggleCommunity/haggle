#include "EffectMgr.hpp"

Sexy::EffectMgr* Sexy::EffectMgr::effect_mgr;

static char* (__fastcall* Sexy__EffectMgr__EffectMgr_)(Sexy::EffectMgr*, char*);
char* __fastcall Sexy__Template__Template(Sexy::EffectMgr* this_, char* edx)
{
	Sexy::EffectMgr::effect_mgr = this_;
	return Sexy__EffectMgr__EffectMgr_(this_, edx);
}

void Sexy::EffectMgr::setup()
{
	MH_CreateHook((void*)0x004471E0, Sexy__Template__Template, (void**)&Sexy__EffectMgr__EffectMgr_);
}

bool Sexy::EffectMgr::check_exists()
{
	if (Sexy::EffectMgr::effect_mgr == 0x0) return false;
	return true;
}

void Sexy::EffectMgr::AddPyramid(float a2, float a3)
{
	if (!Sexy::EffectMgr::check_exists()) return;
	reinterpret_cast<void(__thiscall*)(Sexy::EffectMgr*, float, float)>(0x00450C60)(Sexy::EffectMgr::effect_mgr, a2, a3);
}