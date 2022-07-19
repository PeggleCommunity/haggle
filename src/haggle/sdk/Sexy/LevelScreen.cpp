#include "LevelScreen.hpp"
#include "ThunderballApp.hpp"

Sexy::LevelScreen* Sexy::LevelScreen::level_screen;

static char* (__fastcall* Sexy__LevelScreen__LevelScreen_)(Sexy::LevelScreen*, char*, Sexy::ThunderballApp*);
char* __fastcall Sexy__LevelScreen__LevelScreen(Sexy::LevelScreen* this_, char* edx, Sexy::ThunderballApp* thunderball)
{
	Sexy::LevelScreen::level_screen = this_;
	return Sexy__LevelScreen__LevelScreen_(this_, edx, thunderball);
}

void Sexy::LevelScreen::setup()
{
	MH_CreateHook((void*)0x004AF150, Sexy__LevelScreen__LevelScreen, (void**)&Sexy__LevelScreen__LevelScreen_);
}

bool Sexy::LevelScreen::check_exists()
{
	if (Sexy::LevelScreen::level_screen == 0x0) return false;
	return true;
}

int Sexy::LevelScreen::DoPlay(int a3)
{
	if (!Sexy::LevelScreen::check_exists()) return -1;
	return reinterpret_cast<int(__thiscall*)(Sexy::LevelScreen*, int)>(0x00493530)(Sexy::LevelScreen::level_screen, a3);
}
