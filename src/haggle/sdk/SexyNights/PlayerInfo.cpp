#include "PlayerInfo.hpp"
#include "callbacks/callbacks.hpp"

SexyNights::PlayerInfo* SexyNights::PlayerInfo::player_info;

static char* (__fastcall* SexyNights__PlayerInfo__PlayerInfo_)(SexyNights::PlayerInfo*, char*);
char* __fastcall SexyNights__PlayerInfo__PlayerInfo(SexyNights::PlayerInfo* this_, char* edx)
{
	SexyNights::PlayerInfo::player_info = this_;
	return SexyNights__PlayerInfo__PlayerInfo_(this_, edx);
}

static bool (__fastcall* SexyNights__PlayerInfo__JustBeatAdventure_)(SexyNights::PlayerInfo*, char*);
bool __fastcall SexyNights__PlayerInfo__JustBeatAdventure(SexyNights::PlayerInfo* this_, char* edx)
{
	auto retn = SexyNights__PlayerInfo__JustBeatAdventure_(this_, edx);
	if (retn) callbacks::run_basic_callbacks(callbacks::type::just_beat_adventure_true);
	else if(!retn) callbacks::run_basic_callbacks(callbacks::type::just_beat_adventure_false);
	return retn;
}

void SexyNights::PlayerInfo::setup()
{
	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			MH_CreateHook((void*)0x00429200, SexyNights__PlayerInfo__PlayerInfo, (void**)&SexyNights__PlayerInfo__PlayerInfo_);
			MH_CreateHook((void*)0x00403870, SexyNights__PlayerInfo__JustBeatAdventure, (void**)&SexyNights__PlayerInfo__JustBeatAdventure_);
		} break;
	}
}

bool SexyNights::PlayerInfo::check_exists()
{
	if (SexyNights::PlayerInfo::player_info == 0x0) return false;
	return true;
}
