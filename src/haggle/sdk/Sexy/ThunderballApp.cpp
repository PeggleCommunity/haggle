#include "ThunderballApp.hpp"
#include "callbacks/callbacks.hpp"

//For implementation later
Sexy::ThunderballApp* Sexy::ThunderballApp::thunderball = reinterpret_cast<Sexy::ThunderballApp*>(0x0019F3D4);

//Runs on adventure restart
static int (__fastcall* Sexy__ThunderballApp__ShowAdventureScreen_)(Sexy::ThunderballApp*, char*);
int __fastcall Sexy__ThunderballApp__ShowAdventureScreen(Sexy::ThunderballApp* this_, char* edx)
{
	Sexy::callbacks::run_basic_callbacks(Sexy::callbacks::type::show_adventure_screen);
	auto retn = Sexy__ThunderballApp__ShowAdventureScreen_(this_, edx);
	Sexy::callbacks::run_basic_callbacks(Sexy::callbacks::type::after_show_adventure_screen);
	return retn;
}

//Runs on completely new game
static int(__fastcall* Sexy__ThunderballApp__StartAdventureGame_)(Sexy::ThunderballApp*, char*);
int __fastcall Sexy__ThunderballApp__StartAdventureGame(Sexy::ThunderballApp* this_, char* edx)
{
	Sexy::callbacks::run_basic_callbacks(Sexy::callbacks::type::start_adventure_game);
	auto retn = Sexy__ThunderballApp__StartAdventureGame_(this_, edx);
	Sexy::callbacks::run_basic_callbacks(Sexy::callbacks::type::after_start_adventure_game);
	return retn;
}

static void(__fastcall* Sexy__ThunderballApp__DoToMenu_)(Sexy::ThunderballApp*, char*);
void __fastcall Sexy__ThunderballApp__DoToMenu(Sexy::ThunderballApp* this_, char* edx)
{
	Sexy::callbacks::run_basic_callbacks(Sexy::callbacks::type::do_to_menu);
	Sexy__ThunderballApp__DoToMenu_(this_, edx);
}

static int(__fastcall* Sexy__ThunderballApp__DoOptionsDialog_)(Sexy::ThunderballApp*, char*);
int __fastcall Sexy__ThunderballApp__DoOptionsDialog(Sexy::ThunderballApp* this_, char* edx)
{
	Sexy::callbacks::run_basic_callbacks(Sexy::callbacks::type::do_options_dialog);
	return Sexy__ThunderballApp__DoOptionsDialog_(this_, edx);
}

static int(__fastcall* Sexy__ThunderballApp__FinishOptionsDialog_)(Sexy::ThunderballApp*, char*, bool, bool);
int __fastcall Sexy__ThunderballApp__FinishOptionsDialog(Sexy::ThunderballApp* this_, char* edx, bool a2, bool a3)
{
	Sexy::callbacks::run_basic_callbacks(Sexy::callbacks::type::finish_options_dialog);
	return Sexy__ThunderballApp__FinishOptionsDialog_(this_, edx, a2, a3);
}

static void(__fastcall* Sexy__ThunderballApp__ShowLevelScreen_)(Sexy::ThunderballApp*, char*, bool);
void __fastcall Sexy__ThunderballApp__ShowLevelScreen(Sexy::ThunderballApp* this_, char* edx, bool a2)
{
	Sexy::callbacks::run_basic_callbacks(Sexy::callbacks::type::show_level_screen);
	Sexy__ThunderballApp__ShowLevelScreen_(this_, edx, a2);
	Sexy::callbacks::run_basic_callbacks(Sexy::callbacks::type::after_show_level_screen);
}

static void(__fastcall* Sexy__ThunderballApp__PlaySong_)(Sexy::ThunderballApp*, char*, int, char);
void __fastcall Sexy__ThunderballApp__PlaySong(Sexy::ThunderballApp* this_, char* edx, int a2, char a3)
{
	Sexy__ThunderballApp__PlaySong_(this_, edx, a2, a3);
}

static bool(__fastcall* Sexy__ThunderballApp__IsTrialOver_)(Sexy::ThunderballApp*, char*);
bool __fastcall Sexy__ThunderballApp__IsTrialOver(Sexy::ThunderballApp* this_, char* edx)
{
#ifdef DEBUG
	return false;
#else
	return Sexy__ThunderballApp__IsTrialOver_(this_, edx);
#endif
}

static bool(__fastcall* Sexy__ThunderballApp__IsLevelLockedTrial_)(Sexy::ThunderballApp*, char*);
bool __fastcall Sexy__ThunderballApp__IsLevelLockedTrial(Sexy::ThunderballApp* this_, char* edx)
{
#ifdef DEBUG
	return false;
#else
	return Sexy__ThunderballApp__IsLevelLockedTrial_(this_, edx);
#endif
}

static bool(__fastcall* Sexy__ThunderballApp__IsRegistered_)(Sexy::ThunderballApp*, char*);
bool __fastcall Sexy__ThunderballApp__IsRegistered(Sexy::ThunderballApp* this_, char* edx)
{
#ifdef DEBUG
	return true;
#else
	return Sexy__ThunderballApp__IsRegistered_(this_, edx);
#endif
}


void Sexy::ThunderballApp::setup()
{
	MH_CreateHook((void*)0x00429890, Sexy__ThunderballApp__ShowAdventureScreen, (void**)&Sexy__ThunderballApp__ShowAdventureScreen_);
	MH_CreateHook((void*)0x0042FF70, Sexy__ThunderballApp__StartAdventureGame, (void**)&Sexy__ThunderballApp__StartAdventureGame_);
	MH_CreateHook((void*)0x0042D7A0, Sexy__ThunderballApp__DoToMenu, (void**)&Sexy__ThunderballApp__DoToMenu_);
	MH_CreateHook((void*)0x0040C210, Sexy__ThunderballApp__DoOptionsDialog, (void**)&Sexy__ThunderballApp__DoOptionsDialog_);
	MH_CreateHook((void*)0x0041C840, Sexy__ThunderballApp__FinishOptionsDialog, (void**)&Sexy__ThunderballApp__FinishOptionsDialog_);
	MH_CreateHook((void*)0x0042D350, Sexy__ThunderballApp__ShowLevelScreen, (void**)&Sexy__ThunderballApp__ShowLevelScreen_);
	MH_CreateHook((void*)0x0040BDD0, Sexy__ThunderballApp__PlaySong, (void**)&Sexy__ThunderballApp__PlaySong_);
	MH_CreateHook((void*)0x00405D90, Sexy__ThunderballApp__IsTrialOver, (void**)&Sexy__ThunderballApp__IsTrialOver_);
	MH_CreateHook((void*)0x00405860, Sexy__ThunderballApp__IsLevelLockedTrial, (void**)&Sexy__ThunderballApp__IsLevelLockedTrial_);
	MH_CreateHook((void*)0x004057D0, Sexy__ThunderballApp__IsRegistered, (void**)&Sexy__ThunderballApp__IsRegistered_);
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

int Sexy::ThunderballApp::ShowBoard(Sexy::ThunderballApp* thunderball, bool a2, bool a3)
{
	if (!thunderball) return -1;
	return reinterpret_cast<int(__thiscall*)(Sexy::ThunderballApp*, bool, bool)>(0x0042F860)(thunderball, a2, a3);
}

int Sexy::ThunderballApp::ShowBoard(bool a2, bool a3)
{
	return Sexy::ThunderballApp::ShowBoard(Sexy::ThunderballApp::thunderball, a2, a3);
}

void Sexy::ThunderballApp::SetColorblind(bool what)
{
	if (!thunderball) return;
	reinterpret_cast<int(__thiscall*)(Sexy::ThunderballApp*, bool)>(0x0041C810)(thunderball, what);
}

void Sexy::ThunderballApp::PlaySong(Sexy::ThunderballApp* thunderball, int a2, char a3)
{
	if (!Sexy::ThunderballApp::thunderball) return;
	return reinterpret_cast<void(__thiscall*)(Sexy::ThunderballApp*, int, char)>(0x0040BDD0)(thunderball, a2, a3);
}

void Sexy::ThunderballApp::PlaySong(int a2, char a3)
{
	return Sexy::ThunderballApp::PlaySong(Sexy::ThunderballApp::thunderball, a2, a3);
}
