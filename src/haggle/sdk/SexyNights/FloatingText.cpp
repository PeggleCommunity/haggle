#include "FloatingText.hpp"

SexyNights::FloatingText* SexyNights::FloatingText::floating_text;

static char* (__fastcall* SexyNights__FloatingText__FloatingText_)(SexyNights::FloatingText*, char*);
char* __fastcall SexyNights__FloatingText__FloatingText(SexyNights::FloatingText* this_, char* edx)
{
	SexyNights::FloatingText::floating_text = this_;
	return SexyNights__FloatingText__FloatingText_(this_, edx);
}

void SexyNights::FloatingText::setup()
{

}

bool SexyNights::FloatingText::check_exists()
{
	if (SexyNights::FloatingText::floating_text == 0x0) return false;
	return true;
}
