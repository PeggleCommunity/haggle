#include "LogicMgr.hpp"
#include "utils/memory.hpp"
#include "callbacks/callbacks.hpp"

SexyNights::LogicMgr* SexyNights::LogicMgr::logic_mgr;

static char* (__stdcall* SexyNights__LogicMgr__LogicMgr_)(SexyNights::LogicMgr*, int);
char* __stdcall SexyNights__LogicMgr__LogicMgr(SexyNights::LogicMgr* this_, int a2)
{
	SexyNights::LogicMgr::logic_mgr = this_;
	return SexyNights__LogicMgr__LogicMgr_(this_, a2);
}

static char* (__fastcall* SexyNights__LogicMgr__LogicMgr_dtor_)(SexyNights::LogicMgr*, char*);
char* __fastcall SexyNights__LogicMgr__LogicMgr_dtor(SexyNights::LogicMgr* this_, char* edx)
{
	SexyNights::LogicMgr::logic_mgr = nullptr;
	return SexyNights__LogicMgr__LogicMgr_dtor_(this_, edx);
}

static void(__fastcall* SexyNights__LogicMgr__DoPowerup_)(SexyNights::LogicMgr*, char*, SexyNights::Ball*, SexyNights::PhysObj*, int, int);
void __fastcall SexyNights__LogicMgr__DoPowerup(SexyNights::LogicMgr* this_, char* edx, SexyNights::Ball* a2, SexyNights::PhysObj* a3, int powerup, int a5)
{
	return SexyNights__LogicMgr__DoPowerup_(this_, edx, a2, a3, powerup, a5);
}

static void(__fastcall* SexyNights__LogicMgr__BeginTurn2_)(SexyNights::LogicMgr*, char*);
void __fastcall SexyNights__LogicMgr__BeginTurn2(SexyNights::LogicMgr* this_, char* edx)
{
	SexyNights::callbacks::run_basic_callbacks(SexyNights::callbacks::type::begin_turn_2);
	SexyNights__LogicMgr__BeginTurn2_(this_, edx);
	SexyNights::callbacks::run_after_begin_turn_2_callbacks(this_);
}

void SexyNights::LogicMgr::setup()
{
	MH_CreateHook((void*)0x00466C30, SexyNights__LogicMgr__LogicMgr, (void**)&SexyNights__LogicMgr__LogicMgr_);
	MH_CreateHook((void*)0x00466E80, SexyNights__LogicMgr__LogicMgr_dtor, (void**)&SexyNights__LogicMgr__LogicMgr_dtor_);
	MH_CreateHook((void*)0x0046E9C0, SexyNights__LogicMgr__DoPowerup, (void**)&SexyNights__LogicMgr__DoPowerup_);
	//MH_CreateHook((void*)0x004701B0, SexyNights__LogicMgr__PegHit, (void**)&SexyNights__LogicMgr__PegHit_);

	//MH_CreateHook((void*)0x0046C230, SexyNights__LogicMgr__BeginShot, (void**)&SexyNights__LogicMgr__BeginShot_);
	MH_CreateHook((void*)0x0046B950, SexyNights__LogicMgr__BeginTurn2, (void**)&SexyNights__LogicMgr__BeginTurn2_);
	//MH_CreateHook((void*)0x0046C220, SexyNights__LogicMgr__FinishInitLevelText, (void**)&SexyNights__LogicMgr__FinishInitLevelText_);
	//MH_CreateHook((void*)0x0046BE60, SexyNights__LogicMgr__DoLevelDone, (void**)&SexyNights__LogicMgr__DoLevelDone_);
	//MH_CreateHook((void*)0x0046BA90, SexyNights__LogicMgr__BeatLevel, (void**)&SexyNights__LogicMgr__BeatLevel_);
}

bool SexyNights::LogicMgr::check_exists()
{
	if (logic_mgr != nullptr)
	{
		return true;
	}
	return false;
}

void SexyNights::LogicMgr::DoPowerup(SexyNights::Ball* ball, SexyNights::PhysObj* phys_obj, int powerup, int a5)
{
	if (!check_exists()) return;
	reinterpret_cast<void(__thiscall*)(LogicMgr*, SexyNights::Ball*, SexyNights::PhysObj*, int, int)>(0x0046E9C0)
		(logic_mgr, ball, phys_obj, powerup, a5);
}

void SexyNights::LogicMgr::ActivatePowerup(int powerup, int a3)
{
	if (!check_exists()) return;
	reinterpret_cast<void(__thiscall*)(LogicMgr*, int, int)>(0x0046AA40)(logic_mgr, powerup, a3);
}

SexyNights::FloatingText* SexyNights::LogicMgr::AddStandardText(std::string& string, float x_pos, float y_pos, int type)
{
	if (!check_exists()) return 0;
	return reinterpret_cast<SexyNights::FloatingText * (__thiscall*)(LogicMgr*, std::string&, float, float, int)>(0x00468DD0)
		(logic_mgr, string, x_pos, y_pos, type);
}

bool SexyNights::LogicMgr::BeginTurn2()
{
	if (!check_exists()) return false;
	return reinterpret_cast<bool(__thiscall*)(LogicMgr*)>(0x0046B950)(logic_mgr);
}
