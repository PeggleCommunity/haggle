#include "ThunderballApp.hpp"
#include "callbacks/callbacks.hpp"

//For implementation later
Sexy::ThunderballApp* Sexy::ThunderballApp::thunderball = *reinterpret_cast<Sexy::ThunderballApp**>(0x00687394);

//Runs on adventure restart
static int (__fastcall* Sexy__ThunderballApp__ShowAdventureScreen_)(Sexy::ThunderballApp*, char*);
int __fastcall Sexy__ThunderballApp__ShowAdventureScreen(Sexy::ThunderballApp* this_, char* edx)
{
	callbacks::run_basic_callbacks(callbacks::type::show_adventure_screen);
	auto retn = Sexy__ThunderballApp__ShowAdventureScreen_(this_, edx);
	callbacks::run_basic_callbacks(callbacks::type::after_show_adventure_screen);
	return retn;
}

//Runs on completely new game
static int(__fastcall* Sexy__ThunderballApp__StartAdventureGame_)(Sexy::ThunderballApp*, char*);
int __fastcall Sexy__ThunderballApp__StartAdventureGame(Sexy::ThunderballApp* this_, char* edx)
{
	callbacks::run_basic_callbacks(callbacks::type::start_adventure_game);
	auto retn = Sexy__ThunderballApp__StartAdventureGame_(this_, edx);
	callbacks::run_basic_callbacks(callbacks::type::after_start_adventure_game);
	return retn;
}

void Sexy::ThunderballApp::setup()
{
	MH_CreateHook((void*)0x00429890, Sexy__ThunderballApp__ShowAdventureScreen, (void**)&Sexy__ThunderballApp__ShowAdventureScreen_);
	MH_CreateHook((void*)0x0042FF70, Sexy__ThunderballApp__StartAdventureGame, (void**)&Sexy__ThunderballApp__StartAdventureGame_);
}

bool Sexy::ThunderballApp::check_exists()
{
	if (Sexy::ThunderballApp::thunderball == 0x0) return false;
	return true;
}
