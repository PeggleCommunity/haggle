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

void SexyNights::LogicMgr::setup()
{
	MH_CreateHook((void*)0x00466C30, SexyNights__LogicMgr__LogicMgr, (void**)&SexyNights__LogicMgr__LogicMgr_);
	//MH_CreateHook((void*)0x0046E9C0, SexyNights__LogicMgr__DoPowerup, (void**)&SexyNights__LogicMgr__DoPowerup_);
	//MH_CreateHook((void*)0x004701B0, SexyNights__LogicMgr__PegHit, (void**)&SexyNights__LogicMgr__PegHit_);

	//MH_CreateHook((void*)0x0046C230, SexyNights__LogicMgr__BeginShot, (void**)&SexyNights__LogicMgr__BeginShot_);
	//MH_CreateHook((void*)0x0046B950, SexyNights__LogicMgr__BeginTurn2, (void**)&SexyNights__LogicMgr__BeginTurn2_);
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

	//int* checkPtr = reinterpret_cast<int*>(0x00687394);  // ThunderballApp pointer (static)
	//if (reinterpret_cast<int*>(*checkPtr) == nullptr)
	//{
	//	logic_mgr = nullptr;
	//	return false;
	//}

	//checkPtr = reinterpret_cast<int*>(*checkPtr + 0x7B8);  // Board pointer (dynamic)
	//if (reinterpret_cast<int*>(*checkPtr) == nullptr)
	//{
	//	logic_mgr = nullptr;
	//	return false;
	//}

	//checkPtr = reinterpret_cast<int*>(*checkPtr + 0x154);  // LogicMgr pointer (dynamic)
	//if (reinterpret_cast<int*>(*checkPtr) == nullptr)
	//{
	//	logic_mgr = nullptr;
	//	return false;
	//}

	return TryPointerRefresh();  // The static LogicMgr pointer was null, but it looks like the LogicMgr exists in the game memory. Try to retrieve it.
}

bool SexyNights::LogicMgr::TryPointerRefresh()
{
	int* checkPtr = nullptr;

	//checkPtr = reinterpret_cast<int*>(0x00687394);  // ThunderballApp pointer (static)
	//if (reinterpret_cast<int*>(*checkPtr) == nullptr)
	//{
	//	logic_mgr = nullptr;
	//	return false;
	//}

	//checkPtr = reinterpret_cast<int*>(*checkPtr + 0x7B8);  // Board pointer (dynamic)
	//if (reinterpret_cast<int*>(*checkPtr) == nullptr)
	//{
	//	logic_mgr = nullptr;
	//	return false;
	//}

	//checkPtr = reinterpret_cast<int*>(*checkPtr + 0x154);  // LogicMgr pointer (dynamic)
	//if (reinterpret_cast<int*>(*checkPtr) == nullptr)
	//{
	//	logic_mgr = nullptr;
	//	return false;
	//}

	if (!checkPtr) return false;
	logic_mgr = reinterpret_cast<LogicMgr*>(*checkPtr);
	return logic_mgr != 0;
}

void SexyNights::LogicMgr::DoPowerup(SexyNights::Ball* ball, SexyNights::PhysObj* phys_obj, int powerup, int a5)
{
	if (!check_exists()) return;
	reinterpret_cast<void(__thiscall*)(LogicMgr*, SexyNights::Ball*, SexyNights::PhysObj*, int, int)>(0x0046E9C0)
		(logic_mgr, ball, phys_obj, powerup, a5);
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
