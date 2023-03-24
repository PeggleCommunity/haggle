#include "SoundMgr.hpp"

SexyNights::SoundMgr* SexyNights::SoundMgr::sound_mgr;

static char* (__fastcall* SexyNights__SoundMgr__SoundMgr_)(SexyNights::SoundMgr*, char*);
char* __fastcall SexyNights__SoundMgr__SoundMgr(SexyNights::SoundMgr* this_, char* edx)
{
	SexyNights::SoundMgr::sound_mgr = this_;
	return SexyNights__SoundMgr__SoundMgr_(this_, edx);
}

void SexyNights::SoundMgr::setup()
{

}

bool SexyNights::SoundMgr::check_exists()
{
	if (SexyNights::SoundMgr::sound_mgr == 0x0) return false;
	return true;
}

void SexyNights::SoundMgr::AddSound(int a2, float a3, int a4, int a5, int a6, float a7)
{
	if (!SexyNights::SoundMgr::check_exists()) return;
	reinterpret_cast<void(__thiscall*)(SexyNights::SoundMgr*, int, float, int, int, int, float)>
		(0x00478A50)(SexyNights::SoundMgr::sound_mgr, a2, a3, a4, a5, a6, a7);
}
