#include "CharacterMgr.hpp"

Sexy::CharacterMgr* Sexy::CharacterMgr::character_mgr;

static char* (__fastcall* Sexy__CharacterMgr__CharacterMgr_)(Sexy::CharacterMgr*, char*);
char* __fastcall Sexy__CharacterMgr__CharacterMgr(Sexy::CharacterMgr* this_, char* edx)
{
	Sexy::CharacterMgr::character_mgr = this_;
	return Sexy__CharacterMgr__CharacterMgr(this_, edx);
}

void Sexy::CharacterMgr::setup()
{
	MH_CreateHook((void*)0x00473C30, Sexy__CharacterMgr__CharacterMgr, (void**)&Sexy__CharacterMgr__CharacterMgr_);
}

bool Sexy::CharacterMgr::check_exists()
{
	if (Sexy::CharacterMgr::character_mgr == 0x0) return false;
	return true;
}