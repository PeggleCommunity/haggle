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
	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			MH_CreateHook((void*)0x004238A0, Sexy__Board__Board, (void**)&Sexy__Board__Board_);
			MH_CreateHook((void*)0x0042AAE0, Sexy__Board__LoadLevel, (void**)&Sexy__Board__LoadLevel_);
		} break;
	}
}

bool Sexy::Board::check_exists()
{
	if (Sexy::Board::board == 0x0) return false;
	return true;
}

void Sexy::Board::Reload()
{
	std::uint32_t address;

	switch (version)
	{
	case PeggleVersion::Deluxe101:
		address = 0x004090D0;
		break;
	}

	if (!Sexy::Board::check_exists() || !address) return;
	reinterpret_cast<void(__thiscall*)(Sexy::Board*)>(address)(Sexy::Board::board);
}

void Sexy::Board::KeyDown(KeyCode keyCodePressed)
{
	std::uint32_t address;

	switch (version)
	{
	case PeggleVersion::Deluxe101:
		address = 0x00402930;
		break;
	}

	if (!Sexy::Board::check_exists() || !address) return;
	reinterpret_cast<void(__thiscall*)(Sexy::Board*, KeyCode)>(address)(Sexy::Board::board, keyCodePressed);
}

void Sexy::Board::SetSlowMo(bool a2, int a3)
{
	std::uint32_t address;

	switch (version)
	{
	case PeggleVersion::Deluxe101:
		address = 0x004026F0;
		break;
	}

	if (!Sexy::Board::check_exists() || !address) return;
	reinterpret_cast<void(__thiscall*)(Sexy::Board*, bool, int)>(address)(Sexy::Board::board, a2, a3);
}

int Sexy::Board::Reset()
{
	std::uint32_t address = 0x0;

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			address = 0x0042DA00;
		} break;
	}

	if (!Sexy::Board::check_exists() || !address) return -1;
	return reinterpret_cast<int(__thiscall*)(Sexy::Board*)>(address)(Sexy::Board::board);
}

void Sexy::Board::SyncColorblind()
{
	std::uint32_t address = 0x0;

	switch (version)
	{
	case PeggleVersion::Deluxe101:
	{
		address = 0x004098B0;
	} break;
	}

	if (!Sexy::Board::check_exists() || !address) return;
	reinterpret_cast<int(__thiscall*)(Sexy::Board*)>(address)(Sexy::Board::board);
}
