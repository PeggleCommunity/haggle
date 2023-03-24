#include "StageMgr.hpp"

SexyNights::StageMgr* SexyNights::StageMgr::stage_mgr;

static char* (__fastcall* SexyNights__StageMgr__StageMgr_)(SexyNights::StageMgr*, char*);
char* __fastcall SexyNights__StageMgr__StageMgr(SexyNights::StageMgr* this_, char* edx)
{
	SexyNights::StageMgr::stage_mgr = this_;
	return SexyNights__StageMgr__StageMgr_(this_, edx);
}

void SexyNights::StageMgr::setup()
{

}

bool SexyNights::StageMgr::check_exists()
{
	if (SexyNights::StageMgr::stage_mgr == 0x0) return false;
	return true;
}
