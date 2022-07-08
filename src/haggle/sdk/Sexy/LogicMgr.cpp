#include "LogicMgr.hpp"
#include "memory.hpp"

Sexy::LogicMgr* Sexy::LogicMgr::logic_mgr;

static char* (__fastcall * Sexy__LogicMgr__LogicMgr_)(Sexy::LogicMgr*, char*, char*);
char* __fastcall Sexy__LogicMgr__LogicMgr(Sexy::LogicMgr* this_, char* edx, char* thunderball)
{
	Sexy::LogicMgr::logic_mgr = this_;
	return Sexy__LogicMgr__LogicMgr_(this_, edx, thunderball);
}

static void (__fastcall* Sexy__LogicMgr__DoPowerup_)(Sexy::LogicMgr*, char*, Sexy::Ball*, Sexy::PhysObj*, int, int);
void __fastcall Sexy__LogicMgr__DoPowerup(Sexy::LogicMgr* this_, char* edx, Sexy::Ball* a2, Sexy::PhysObj* a3, int powerup, int a5)
{
	return Sexy__LogicMgr__DoPowerup_(this_, edx, a2, a3, powerup, a5);
}

static void (__fastcall* Sexy__LogicMgr__PegHit_)(Sexy::LogicMgr*, char*, Sexy::Ball*, Sexy::PhysObj*, bool);
void __fastcall Sexy__LogicMgr__PegHit(Sexy::LogicMgr* this_, char* edx, Sexy::Ball* ball, Sexy::PhysObj* phys_obj, bool a4)
{
	return Sexy__LogicMgr__PegHit_(this_, edx, ball, phys_obj, a4);
}

static void(__fastcall* Sexy__LogicMgr__BeginShot_)(Sexy::LogicMgr*, char*, bool);
void __fastcall Sexy__LogicMgr__BeginShot(Sexy::LogicMgr* this_, char* edx, bool a2)
{
	return Sexy__LogicMgr__BeginShot_(this_, edx, a2);
}

static char* (__fastcall* Sexy__LogicMgr__BeginTurn2_)(Sexy::LogicMgr*, char*);
char* __fastcall Sexy__LogicMgr__BeginTurn2(Sexy::LogicMgr* this_, char* edx)
{
	return Sexy__LogicMgr__BeginTurn2_(this_, edx);
}

//Adds control over the otherwise broken powerups
void unused_powerups(Sexy::PowerUp powerup)
{
	switch (powerup)
	{
	case Sexy::PowerUp::TimeBomb:
	{
		break;
	}

	case Sexy::PowerUp::Nudge:
	{
		break;
	}
	}
}

void __declspec(naked) unused_powerups_hook()
{
	static constexpr std::uint32_t retn_addr = 0x0046F0E6;
	__asm
	{
		pushad;
		push eax;
		call unused_powerups;
		add esp, 0x04;
		popad;

		push retn_addr;
		retn;
	}
}

void __declspec(naked) next_board_balls_hook()
{
	static constexpr std::uint32_t retn_addr = 0x0045DE61;
	__asm
	{
		mov eax, 10;
		push retn_addr;
		retn;
	}
}

void Sexy::LogicMgr::setup()
{
	MH_CreateHook((void*)0x004610D0, Sexy__LogicMgr__LogicMgr, (void**)&Sexy__LogicMgr__LogicMgr_);
	MH_CreateHook((void*)0x0046EDF0, Sexy__LogicMgr__DoPowerup, (void**)&Sexy__LogicMgr__DoPowerup_);
	MH_CreateHook((void*)0x0046F480, Sexy__LogicMgr__PegHit, (void**)&Sexy__LogicMgr__PegHit_);
	MH_CreateHook((void*)0x0046AC70, Sexy__LogicMgr__BeginShot, (void**)&Sexy__LogicMgr__BeginShot_);
	MH_CreateHook((void*)0x0044B5B0, Sexy__LogicMgr__BeginTurn2, (void**)&Sexy__LogicMgr__BeginTurn2_);

	jump(0x0046F0DF, unused_powerups_hook);
	jump(0x0045DE5C, next_board_balls_hook);
}

bool Sexy::LogicMgr::check_exists()
{
	if (Sexy::LogicMgr::logic_mgr == 0x0) return false;
	return true;
}

Sexy::LogicMgr* Sexy::LogicMgr::IncNumBalls(int top_count, int bottom_count, bool bottom)
{
	if (!Sexy::LogicMgr::check_exists()) return 0;
	
	return reinterpret_cast<Sexy::LogicMgr* (__thiscall*)(Sexy::LogicMgr*, int, int, bool)>(0x0045D880)
		(Sexy::LogicMgr::logic_mgr, top_count, bottom_count, bottom);
}

int __cdecl Sexy::LogicMgr::BeginShot(bool a2)
{
	if (!Sexy::LogicMgr::check_exists()) return 0;

	return reinterpret_cast<int(__thiscall*)(Sexy::LogicMgr*, bool)>(0x0045D880)(Sexy::LogicMgr::logic_mgr, a2);
}

void Sexy::LogicMgr::DoPowerup(Sexy::Ball* ball, Sexy::PhysObj* phys_obj, int powerup, int a5)
{
	if (!Sexy::LogicMgr::check_exists()) return;

	reinterpret_cast<void(__thiscall*)(Sexy::LogicMgr*, Sexy::Ball*, Sexy::PhysObj*, int, int)>(0x0046EDF0)
		(Sexy::LogicMgr::logic_mgr, ball, phys_obj, powerup, a5);
}

void Sexy::LogicMgr::ActivatePowerup(int powerup, int a3)
{
	if (!Sexy::LogicMgr::check_exists()) return;
	reinterpret_cast<void(__thiscall*)(Sexy::LogicMgr*, int, int)>(0x004612E0)(Sexy::LogicMgr::logic_mgr, powerup, a3);
}

std::int64_t Sexy::LogicMgr::DoMultiball(Sexy::Ball* a2, Sexy::PhysObj* a3)
{
	if (!Sexy::LogicMgr::check_exists()) return 0;
	return reinterpret_cast<std::int64_t(__thiscall*)(Sexy::LogicMgr*, Sexy::Ball*, Sexy::PhysObj*)>(0x0046EAD0)(Sexy::LogicMgr::logic_mgr, a2, a3);
}

void Sexy::LogicMgr::PegHit(Sexy::Ball* ball, Sexy::PhysObj* phys_obj, bool a4)
{
	if (!Sexy::LogicMgr::check_exists()) return;
	reinterpret_cast<std::int64_t(__thiscall*)(Sexy::LogicMgr*, Sexy::Ball*, Sexy::PhysObj*, bool)>(0x0046F480)
		(Sexy::LogicMgr::logic_mgr, ball, phys_obj, a4);
}

Sexy::FloatingText* Sexy::LogicMgr::AddStandardText(std::string string, float x_pos, float y_pos, int type)
{
	if (!Sexy::LogicMgr::check_exists()) return 0;
	return reinterpret_cast<Sexy::FloatingText* (__thiscall*)(Sexy::LogicMgr*, std::string&, float, float, int)>(0x00469EB0)
		(Sexy::LogicMgr::logic_mgr, string, x_pos, y_pos, type);
}

Sexy::FloatingText* Sexy::LogicMgr::AddStandardText(const char* string, float pos_x, float pos_y, int type)
{
	return Sexy::LogicMgr::AddStandardText(std::string(string), pos_x, pos_y, type);
}

void Sexy::LogicMgr::DoExploder(Sexy::Ball* ball, Sexy::PhysObj* phys_obj)
{
	if (!Sexy::LogicMgr::check_exists()) return;
	reinterpret_cast<void (__thiscall*)(Sexy::LogicMgr*, Sexy::Ball*, Sexy::PhysObj*)>(0x0045E330)(Sexy::LogicMgr::logic_mgr, ball, phys_obj);
}

bool Sexy::LogicMgr::BeginTurn2()
{
	if (!Sexy::LogicMgr::check_exists()) return false;
	return reinterpret_cast<bool(__thiscall*)(Sexy::LogicMgr*)>(0x0044B5B0)(Sexy::LogicMgr::logic_mgr);
}

void Sexy::LogicMgr::ActivateFreeBall(bool a4)
{
	if (!Sexy::LogicMgr::check_exists()) return;
	reinterpret_cast<void(__thiscall*)(Sexy::LogicMgr*, bool)>(0x00440580)(Sexy::LogicMgr::logic_mgr, a4);
}

void Sexy::LogicMgr::SetWearHat(int a2)
{
	if (!Sexy::LogicMgr::check_exists()) return;
	reinterpret_cast<void(__thiscall*)(Sexy::LogicMgr*, int)>(0x0043D4D0)(Sexy::LogicMgr::logic_mgr, a2);
}

int Sexy::LogicMgr::SetState(int a2)
{
	if (!Sexy::LogicMgr::check_exists()) return 0;
	return reinterpret_cast<int(__thiscall*)(Sexy::LogicMgr*, int)>(0x00436FB0)(Sexy::LogicMgr::logic_mgr, a2);
}

void Sexy::LogicMgr::SetGunAngle(float newAngle)
{
	if (!Sexy::LogicMgr::check_exists()) return;
	reinterpret_cast<void(__thiscall*)(Sexy::LogicMgr*, float)>(0x00436FD0)(Sexy::LogicMgr::logic_mgr, newAngle);
}
