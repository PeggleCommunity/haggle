#include "MainMenu.hpp"

Sexy::MainMenu* Sexy::MainMenu::main_menu;

static char* (__fastcall* Sexy__MainMenu__MainMenu_)(Sexy::MainMenu*, char*);
char* __fastcall Sexy__MainMenu__MainMenu(Sexy::MainMenu* this_, char* edx)
{
	Sexy::MainMenu::main_menu = this_;
	return Sexy__MainMenu__MainMenu_(this_, edx);
}

static void(__fastcall* Sexy__MainMenu__Update_)(Sexy::MainMenu*, char*);
void __fastcall Sexy__MainMenu__Update(Sexy::MainMenu* this_, char* edx)
{
	Sexy__MainMenu__Update_(this_, edx);
}

void Sexy::MainMenu::setup()
{
	MH_CreateHook((void*)0x004A79E0, Sexy__MainMenu__MainMenu, (void**)&Sexy__MainMenu__MainMenu_);
	MH_CreateHook((void*)0x004AF680, Sexy__MainMenu__Update, (void**)&Sexy__MainMenu__Update_);
}

bool Sexy::MainMenu::check_exists()
{
	if (Sexy::MainMenu::main_menu == 0x0) return false;
	return true;
}

void Sexy::MainMenu::StartGame()
{
	if (!Sexy::MainMenu::check_exists()) return;
	reinterpret_cast<void(__thiscall*)(Sexy::MainMenu*)>(0x004A9190)(Sexy::MainMenu::main_menu);
}
