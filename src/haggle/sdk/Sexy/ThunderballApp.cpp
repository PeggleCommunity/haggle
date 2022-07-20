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

static void(__fastcall* Sexy__ThunderballApp__DoToMenu_)(Sexy::ThunderballApp*, char*);
void __fastcall Sexy__ThunderballApp__DoToMenu(Sexy::ThunderballApp* this_, char* edx)
{
	callbacks::run_basic_callbacks(callbacks::type::do_to_menu);
	Sexy__ThunderballApp__DoToMenu_(this_, edx);
}

static int(__fastcall* Sexy__ThunderballApp__DoOptionsDialog_)(Sexy::ThunderballApp*, char*);
int __fastcall Sexy__ThunderballApp__DoOptionsDialog(Sexy::ThunderballApp* this_, char* edx)
{
	callbacks::run_basic_callbacks(callbacks::type::do_options_dialog);
	return Sexy__ThunderballApp__DoOptionsDialog_(this_, edx);
}

static int(__fastcall* Sexy__ThunderballApp__FinishOptionsDialog_)(Sexy::ThunderballApp*, char*, bool, bool);
int __fastcall Sexy__ThunderballApp__FinishOptionsDialog(Sexy::ThunderballApp* this_, char* edx, bool a2, bool a3)
{
	callbacks::run_basic_callbacks(callbacks::type::finish_options_dialog);
	return Sexy__ThunderballApp__FinishOptionsDialog_(this_, edx, a2, a3);
}

static void(__fastcall* Sexy__ThunderballApp__ShowLevelScreen_)(Sexy::ThunderballApp*, char*, bool);
void __fastcall Sexy__ThunderballApp__ShowLevelScreen(Sexy::ThunderballApp* this_, char* edx, bool a2)
{
	Sexy__ThunderballApp__ShowLevelScreen_(this_, edx, a2);
	callbacks::run_basic_callbacks(callbacks::type::after_show_level_screen);
}

void Sexy::ThunderballApp::setup()
{
	MH_CreateHook((void*)0x00429890, Sexy__ThunderballApp__ShowAdventureScreen, (void**)&Sexy__ThunderballApp__ShowAdventureScreen_);
	MH_CreateHook((void*)0x0042FF70, Sexy__ThunderballApp__StartAdventureGame, (void**)&Sexy__ThunderballApp__StartAdventureGame_);
	MH_CreateHook((void*)0x0042D7A0, Sexy__ThunderballApp__DoToMenu, (void**)&Sexy__ThunderballApp__DoToMenu_);
	MH_CreateHook((void*)0x0040C210, Sexy__ThunderballApp__DoOptionsDialog, (void**)&Sexy__ThunderballApp__DoOptionsDialog_);
	MH_CreateHook((void*)0x0041C840, Sexy__ThunderballApp__FinishOptionsDialog, (void**)&Sexy__ThunderballApp__FinishOptionsDialog_);
	MH_CreateHook((void*)0x0042D350, Sexy__ThunderballApp__ShowLevelScreen, (void**)&Sexy__ThunderballApp__ShowLevelScreen_);
}

bool Sexy::ThunderballApp::check_exists()
{
	if (Sexy::ThunderballApp::thunderball == 0x0) return false;
	return true;
}

void Sexy::ThunderballApp::DoToMenu()
{
	if (!Sexy::ThunderballApp::check_exists()) return;
	return reinterpret_cast<void(__thiscall*)(Sexy::ThunderballApp*)>(0x0042D7A0)(Sexy::ThunderballApp::thunderball);
}

int Sexy::ThunderballApp::ShowLevelScreen(bool a2)
{
	if (!Sexy::ThunderballApp::check_exists()) return -1;
	return reinterpret_cast<int(__thiscall*)(Sexy::ThunderballApp*, bool)>(0x0042D350)(Sexy::ThunderballApp::thunderball, a2);
}

int Sexy::ThunderballApp::ShowBoard(bool a2, bool a3)
{
	if (!Sexy::ThunderballApp::check_exists()) return -1;
	return reinterpret_cast<int(__thiscall*)(Sexy::ThunderballApp*, bool, bool)>(0x0042F860)(Sexy::ThunderballApp::thunderball, a2, a3);
}
