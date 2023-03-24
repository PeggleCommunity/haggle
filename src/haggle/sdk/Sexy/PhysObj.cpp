#include "PhysObj.hpp"

float& Sexy::PhysObj::mGravity = *reinterpret_cast<float*>(0x00649D80);

static Sexy::PhysObj(__fastcall* Sexy__PhysObj__PhysObj_)(Sexy::PhysObj*, char*);
Sexy::PhysObj __fastcall Sexy__PhysObj__PhysObj(Sexy::PhysObj* this_, char* edx)
{
	return Sexy__PhysObj__PhysObj_(this_, edx);
}

void Sexy::PhysObj::setup()
{
	MH_CreateHook((void*)0x00480660, Sexy__PhysObj__PhysObj, (void**)&Sexy__PhysObj__PhysObj_);
}

bool Sexy::PhysObj::check_exists()
{
	return true;
}
