#include "PlayerInfo.hpp"
#include "callbacks/callbacks.hpp"

SexyNights::PlayerInfo* SexyNights::PlayerInfo::player_info;

void SexyNights::PlayerInfo::setup()
{

}

bool SexyNights::PlayerInfo::check_exists()
{
	if (SexyNights::PlayerInfo::player_info == 0x0) return false;
	return true;
}
