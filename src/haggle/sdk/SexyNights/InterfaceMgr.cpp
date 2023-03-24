#include "InterfaceMgr.hpp"
#include "Graphics.hpp"

SexyNights::InterfaceMgr* SexyNights::InterfaceMgr::interface_mgr;

static char* (__fastcall* SexyNights__InterfaceMgr__InterfaceMgr_)(SexyNights::InterfaceMgr*, char*, SexyNights::Board*);
char* __fastcall SexyNights__InterfaceMgr__InterfaceMgr(SexyNights::InterfaceMgr* this_, char* edx, SexyNights::Board* board)
{
	SexyNights::InterfaceMgr::interface_mgr = this_;
	return SexyNights__InterfaceMgr__InterfaceMgr_(this_, edx, board);
}

void SexyNights::InterfaceMgr::setup()
{

}

bool SexyNights::InterfaceMgr::check_exists()
{
	if (SexyNights::InterfaceMgr::interface_mgr == 0x0) return false;
	return true;
}
