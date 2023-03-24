#include "Board.hpp"
#include "callbacks/callbacks.hpp"

Sexy::Board* Sexy::Board::board;

static char* (__fastcall* Sexy__Board__Board_)(Sexy::Board*, char*, char*);
char* __fastcall Sexy__Board__Board(Sexy::Board* this_, char* edx, char* thunderball)
{
	Sexy::Board::board = this_;
	return Sexy__Board__Board_(this_, edx, thunderball);
}

static int (__fastcall* Sexy__Board__LoadLevel_)(Sexy::Board*, char*, std::string&);
int __fastcall Sexy__Board__LoadLevel(Sexy::Board* this_, char* edx, std::string& level_name)
{
	callbacks::run_load_level_callbacks(this_, level_name);
	auto retn = Sexy__Board__LoadLevel_(this_, edx, level_name);
	return retn;
}

void Sexy::Board::setup()
{
	MH_CreateHook((void*)0x004238A0, Sexy__Board__Board, (void**)&Sexy__Board__Board_);
	MH_CreateHook((void*)0x0042AAE0, Sexy__Board__LoadLevel, (void**)&Sexy__Board__LoadLevel_);
}

bool Sexy::Board::check_exists()
{
	if (Sexy::Board::board == 0x0) return false;
	return true;
}

void Sexy::Board::Reload()
{
	if (!Sexy::Board::check_exists()) return;
	reinterpret_cast<void(__thiscall*)(Sexy::Board*)>(0x004090D0)(Sexy::Board::board);
}

void Sexy::Board::KeyDown(KeyCode keyCodePressed)
{
	if (!Sexy::Board::check_exists()) return;
	reinterpret_cast<void(__thiscall*)(Sexy::Board*, KeyCode)>(0x00402930)(Sexy::Board::board, keyCodePressed);
}

void Sexy::Board::SetSlowMo(bool a2, int a3)
{
	if (!Sexy::Board::check_exists()) return;
	reinterpret_cast<void(__thiscall*)(Sexy::Board*, bool, int)>(0x004026F0)(Sexy::Board::board, a2, a3);
}

int Sexy::Board::Reset()
{
	if (!Sexy::Board::check_exists()) return -1;
	return reinterpret_cast<int(__thiscall*)(Sexy::Board*)>(0x0042DA00)(Sexy::Board::board);
}

void Sexy::Board::SyncColorblind()
{
	if (!Sexy::Board::check_exists()) return;
	reinterpret_cast<int(__thiscall*)(Sexy::Board*)>(0x004098B0)(Sexy::Board::board);
}
