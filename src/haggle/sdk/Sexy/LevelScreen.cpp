#include "LevelScreen.hpp"
#include "ThunderballApp.hpp"
#include "callbacks/callbacks.hpp"

Sexy::LevelScreen* Sexy::LevelScreen::level_screen;

static char* (__fastcall* Sexy__LevelScreen__LevelScreen_)(Sexy::LevelScreen*, char*, Sexy::ThunderballApp*);
char* __fastcall Sexy__LevelScreen__LevelScreen(Sexy::LevelScreen* this_, char* edx, Sexy::ThunderballApp* thunderball)
{
	Sexy::LevelScreen::level_screen = this_;
	return Sexy__LevelScreen__LevelScreen_(this_, edx, thunderball);
}

static unsigned int(__fastcall* Sexy__LevelScreen__DoPlay_)(Sexy::LevelScreen*, char*, unsigned int);
unsigned int __fastcall Sexy__LevelScreen__DoPlay(Sexy::LevelScreen* this_, char* edx, unsigned int a3)
{
	Sexy::LevelScreen::level_screen = this_;
	callbacks::run_do_play_callbacks(this_, a3);
	auto retn = Sexy__LevelScreen__DoPlay_(this_, edx, a3);
	callbacks::run_after_do_play_callbacks(this_, a3);
	return retn;
}

void Sexy::LevelScreen::setup()
{
	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			MH_CreateHook((void*)0x004AF150, Sexy__LevelScreen__LevelScreen, (void**)&Sexy__LevelScreen__LevelScreen_);
			MH_CreateHook((void*)0x00493530, Sexy__LevelScreen__DoPlay, (void**)&Sexy__LevelScreen__DoPlay_);
		} break;
	}
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
