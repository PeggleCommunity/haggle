#include "Graphics.hpp"
#include "Image.hpp"

Sexy::Graphics * Sexy::Graphics::graphics;

static char* (__fastcall* Sexy__Graphics__Graphics_)(Sexy::Graphics*, char*, Sexy::Image*);
char* __fastcall Sexy__Graphics__Graphics(Sexy::Graphics* this_, char* edx, Sexy::Image* image)
{
	Sexy::Graphics::graphics = this_;
	return Sexy__Graphics__Graphics_(this_, edx, image);
}

void Sexy::Graphics::setup()
{
	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			MH_CreateHook((void*)0x004DD230, Sexy__Graphics__Graphics, (void**)&Sexy__Graphics__Graphics_);
		} break;
	}
}
