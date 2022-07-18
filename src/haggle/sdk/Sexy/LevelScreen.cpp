#include "LevelScreen.hpp"

Sexy::LevelScreen* Sexy::LevelScreen::level_screen;

static char* (__fastcall* Sexy__LevelScreen__LevelScreen_)(Sexy::LevelScreen*, char*);
char* __fastcall Sexy__LevelScreen__LevelScreen(Sexy::LevelScreen* this_, char* edx)
{
	Sexy::LevelScreen::level_screen = this_;
	return Sexy__LevelScreen__LevelScreen_(this_, edx);
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
