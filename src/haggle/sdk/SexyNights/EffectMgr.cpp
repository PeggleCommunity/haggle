#include "EffectMgr.hpp"

SexyNights::EffectMgr* SexyNights::EffectMgr::effect_mgr;

static char* (__fastcall* SexyNights__EffectMgr__EffectMgr_)(SexyNights::EffectMgr*, char*);
char* __fastcall SexyNights__EffectMgr__EffectMgr(SexyNights::EffectMgr* this_, char* edx)
{
	SexyNights::EffectMgr::effect_mgr = this_;
	return SexyNights__EffectMgr__EffectMgr_(this_, edx);
}

void SexyNights::EffectMgr::setup()
{

}

bool SexyNights::EffectMgr::check_exists()
{
	if (SexyNights::EffectMgr::effect_mgr == 0x0) return false;
	return true;
}
