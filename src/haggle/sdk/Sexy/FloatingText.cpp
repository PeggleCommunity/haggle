#include "FloatingText.hpp"

Sexy::FloatingText* Sexy::FloatingText::floating_text;

static char* (__fastcall* Sexy__FloatingText__FloatingText_)(Sexy::FloatingText*, char*);
char* __fastcall Sexy__FloatingText__FloatingText(Sexy::FloatingText* this_, char* edx)
{
	Sexy::FloatingText::floating_text = this_;
	return Sexy__FloatingText__FloatingText_(this_, edx);
}

void Sexy::FloatingText::setup()
{
	//MH_CreateHook((void*)0x0, Sexy__FloatingText__FloatingText, (void**)&Sexy__FloatingText__FloatingText_);
}

bool Sexy::FloatingText::check_exists()
{
	if (Sexy::FloatingText::floating_text == 0x0) return false;
	return true;
}
