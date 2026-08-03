#include "Gun.hpp"

Sexy::Gun* Sexy::Gun::gun;

static Sexy::Gun* (__fastcall* Sexy__Gun__Gun_)(Sexy::Gun*, char*, Sexy::Board*);
Sexy::Gun* __fastcall Sexy__Gun__Gun(Sexy::Gun* this_, char* edx, Sexy::Board* board)
{
	Sexy::Gun::gun = this_;
	return Sexy__Gun__Gun_(this_, edx, board);
}

void Sexy::Gun::setup()
{
	MH_CreateHook((void*)0x00486a90, Sexy__Gun__Gun, (void**)&Sexy__Gun__Gun_);
}

bool Sexy::Gun::check_exists()
{
	if (Sexy::Gun::gun == 0x0) return false;
	return true;
}

void Sexy::Gun::SyncState(Sexy::DataSync* theSync)
{
	if (!Sexy::Gun::check_exists()) return;
	reinterpret_cast<void(__thiscall*)(Sexy::Gun*, Sexy::DataSync*)>(0x004882c0)(Sexy::Gun::gun, theSync);
}

void Sexy::Gun::SetDoBouncyGuide(bool doBouncyGuide)
{
	if (!Sexy::Gun::check_exists()) return;
	reinterpret_cast<void(__thiscall*)(Sexy::Gun*, bool)>(0x0047f6e0)(Sexy::Gun::gun, doBouncyGuide);
}
