#include "CharacterMgr.hpp"

SexyNights::CharacterMgr* SexyNights::CharacterMgr::character_mgr;

static char* (__fastcall* SexyNights__CharacterMgr__CharacterMgr_)(SexyNights::CharacterMgr*, char*);
char* __fastcall SexyNights__CharacterMgr__CharacterMgr(SexyNights::CharacterMgr* this_, char* edx)
{
	SexyNights::CharacterMgr::character_mgr = this_;
	return SexyNights__CharacterMgr__CharacterMgr(this_, edx);
}

void SexyNights::CharacterMgr::setup()
{

}

bool SexyNights::CharacterMgr::check_exists()
{
	if (SexyNights::CharacterMgr::character_mgr == 0x0) return false;
	return true;
}
