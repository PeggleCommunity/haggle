#include "CollisionMgr.hpp"

SexyNights::CollisionMgr* SexyNights::CollisionMgr::collision_mgr;

static char* (__fastcall* SexyNights__CollisionMgr__CollisionMgr_)(SexyNights::CollisionMgr*, char*);
char* __fastcall SexyNights__CollisionMgr__CollisionMgr(SexyNights::CollisionMgr* this_, char* edx)
{
	SexyNights::CollisionMgr::collision_mgr = this_;
	return SexyNights__CollisionMgr__CollisionMgr_(this_, edx);
}

void SexyNights::CollisionMgr::setup()
{

}

bool SexyNights::CollisionMgr::check_exists()
{
	if (SexyNights::CollisionMgr::collision_mgr == 0x0) return false;
	return true;
}
