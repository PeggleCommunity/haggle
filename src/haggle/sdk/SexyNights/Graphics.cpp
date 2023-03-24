#include "Graphics.hpp"
#include "Image.hpp"

SexyNights::Graphics * SexyNights::Graphics::graphics;

static char* (__fastcall* SexyNights__Graphics__Graphics_)(SexyNights::Graphics*, char*, SexyNights::Image*);
char* __fastcall SexyNights__Graphics__Graphics(SexyNights::Graphics* this_, char* edx, SexyNights::Image* image)
{
	SexyNights::Graphics::graphics = this_;
	return SexyNights__Graphics__Graphics_(this_, edx, image);
}

void SexyNights::Graphics::setup()
{

}
