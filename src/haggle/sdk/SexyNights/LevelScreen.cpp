#include "LevelScreen.hpp"
#include "ThunderballApp.hpp"
#include "callbacks/callbacks.hpp"

SexyNights::LevelScreen* SexyNights::LevelScreen::level_screen;

static char* (__fastcall* SexyNights__LevelScreen__LevelScreen_)(SexyNights::LevelScreen*, char*, SexyNights::ThunderballApp*);
char* __fastcall SexyNights__LevelScreen__LevelScreen(SexyNights::LevelScreen* this_, char* edx, SexyNights::ThunderballApp* thunderball)
{
	SexyNights::LevelScreen::level_screen = this_;
	return SexyNights__LevelScreen__LevelScreen_(this_, edx, thunderball);
}

void SexyNights::LevelScreen::setup()
{

}

bool SexyNights::LevelScreen::check_exists()
{
	if (SexyNights::LevelScreen::level_screen == 0x0) return false;
	return true;
}
