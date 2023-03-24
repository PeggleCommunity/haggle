#include "PlayerInfo.hpp"
#include "callbacks/callbacks.hpp"

Sexy::PlayerInfo* Sexy::PlayerInfo::player_info;

static char* (__fastcall* Sexy__PlayerInfo__PlayerInfo_)(Sexy::PlayerInfo*, char*);
char* __fastcall Sexy__PlayerInfo__PlayerInfo(Sexy::PlayerInfo* this_, char* edx)
{
	Sexy::PlayerInfo::player_info = this_;
	return Sexy__PlayerInfo__PlayerInfo_(this_, edx);
}

static bool (__fastcall* Sexy__PlayerInfo__JustBeatAdventure_)(Sexy::PlayerInfo*, char*);
bool __fastcall Sexy__PlayerInfo__JustBeatAdventure(Sexy::PlayerInfo* this_, char* edx)
{
	auto retn = Sexy__PlayerInfo__JustBeatAdventure_(this_, edx);
	if (retn) Sexy::callbacks::run_basic_callbacks(Sexy::callbacks::type::just_beat_adventure_true);
	else if(!retn) Sexy::callbacks::run_basic_callbacks(Sexy::callbacks::type::just_beat_adventure_false);
	return retn;
}

void Sexy::PlayerInfo::setup()
{
	MH_CreateHook((void*)0x00429200, Sexy__PlayerInfo__PlayerInfo, (void**)&Sexy__PlayerInfo__PlayerInfo_);
	MH_CreateHook((void*)0x00403870, Sexy__PlayerInfo__JustBeatAdventure, (void**)&Sexy__PlayerInfo__JustBeatAdventure_);
}

bool Sexy::PlayerInfo::check_exists()
{
	if (Sexy::PlayerInfo::player_info == 0x0) return false;
	return true;
}
