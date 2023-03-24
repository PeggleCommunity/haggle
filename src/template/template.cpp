#include "template.hpp"

Sexy::Template* Sexy::Template::temp;

static char* (__fastcall* Sexy__Template__Template_)(Sexy::Template*, char*);
char* __fastcall Sexy__Template__Template(Sexy::Template* this_, char* edx)
{
	Sexy::Template::temp = this_;
	return Sexy__Template__Template_(this_, edx);
}

void Sexy::Template::setup()
{
	MH_CreateHook((void*)0x0, Sexy__Template__Template, (void**)&Sexy__Template__Template_);
}

bool Sexy::Template::check_exists()
{
	if (Sexy::Template::temp == 0x0) return false;
	return true;
}