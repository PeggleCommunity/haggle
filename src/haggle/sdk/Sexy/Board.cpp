#include "Board.hpp"

Sexy::Board* Sexy::Board::board;

static char* (__fastcall* Sexy__Board__Board_)(Sexy::Board*, char*, char*);
char* __fastcall Sexy__Board__Board(Sexy::Board* this_, char* edx, char* thunderball)
{
	Sexy::Board::board = this_;
	return Sexy__Board__Board_(this_, edx, thunderball);
}

void Sexy::Board::setup()
{
	MH_CreateHook((void*)0x004238A0, Sexy__Board__Board, (void**)&Sexy__Board__Board_);
}

bool Sexy::Board::check_exists()
{
	if (Sexy::Board::board == 0x0) return false;
	return true;
}

void Sexy::Board::Reload(Sexy::Board* input)
{
	if (!Sexy::Board::check_exists()) return;
	reinterpret_cast<void(__thiscall*)(Sexy::Board*)>(0x004090D0)(input);
}