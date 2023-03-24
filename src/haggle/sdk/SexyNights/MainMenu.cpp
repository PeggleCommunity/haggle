#include "MainMenu.hpp"
#include "sdk/SexyNightsSDK.hpp"

SexyNights::MainMenu* SexyNights::MainMenu::main_menu;

static void (__fastcall* SexyNights__MainMenu__MainMenu_)(SexyNights::MainMenu*, char*, SexyNights::ThunderballApp* thunderball);
void __fastcall SexyNights__MainMenu__MainMenu(SexyNights::MainMenu* this_, char* edx, SexyNights::ThunderballApp* thunderball)
{
	SexyNights::MainMenu::main_menu = this_;
	SexyNights__MainMenu__MainMenu_(this_, edx, thunderball);
}

void SexyNights::MainMenu::setup()
{

}

bool SexyNights::MainMenu::check_exists()
{
	if (SexyNights::MainMenu::main_menu == 0x0) return false;
	return true;
}
