#include "CollisionMgr.hpp"

Sexy::CollisionMgr* Sexy::CollisionMgr::collision_mgr;

static char* (__fastcall* Sexy__CollisionMgr__CollisionMgr_)(Sexy::CollisionMgr*, char*);
char* __fastcall Sexy__CollisionMgr__CollisionMgr(Sexy::CollisionMgr* this_, char* edx)
{
	Sexy::CollisionMgr::collision_mgr = this_;
	return Sexy__CollisionMgr__CollisionMgr_(this_, edx);
}

void Sexy::CollisionMgr::setup()
{
	MH_CreateHook((void*)0x0044D870, Sexy__CollisionMgr__CollisionMgr, (void**)&Sexy__CollisionMgr__CollisionMgr_);
}

bool Sexy::CollisionMgr::check_exists()
{
	if (Sexy::CollisionMgr::collision_mgr == 0x0) return false;
	return true;
}
