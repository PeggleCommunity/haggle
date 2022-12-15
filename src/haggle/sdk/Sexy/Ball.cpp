#include "Ball.hpp"

Sexy::Ball* Sexy::Ball::ball;

static Sexy::Ball* (__fastcall* Sexy__Ball__Ball_)(Sexy::Ball*, char*, bool);
Sexy::Ball* __fastcall Sexy__Ball__Ball(Sexy::Ball* this_, char* edx, bool a2)
{
	Sexy::Ball::ball = this_;
	return Sexy__Ball__Ball_(this_, edx, a2);
}

void Sexy::Ball::setup()
{
	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			MH_CreateHook((void*)0x00480DE0, Sexy__Ball__Ball, (void**)&Sexy__Ball__Ball_);
		} break;
	}
}

bool Sexy::Ball::check_exists()
{
	if (Sexy::Ball::ball == 0x0) return false;
	return true;
}

void Sexy::Ball::SetPos(float x_pos, float y_pos)
{
	std::uint32_t address = 0x0;

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			address = 0x00474E60;
		} break;
	}

	if (!Sexy::Ball::check_exists() || !address) return;
	reinterpret_cast<void(__thiscall*)(Sexy::Ball*, float, float)>(address)(Sexy::Ball::ball, x_pos, y_pos);
}


void Sexy::Ball::SetVelocity(float x_velo, float y_velo)
{
	std::uint32_t address = 0x0;

	switch (version)
	{
	case PeggleVersion::Deluxe101:
	{
		address = 0x00475600;
	} break;
	}

	if (!Sexy::Ball::check_exists() || !address) return;
	reinterpret_cast<void(__thiscall*)(Sexy::Ball*, float, float)>(address)(Sexy::Ball::ball, x_velo, y_velo);
}
