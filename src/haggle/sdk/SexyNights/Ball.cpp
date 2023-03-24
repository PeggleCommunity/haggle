#include "Ball.hpp"

SexyNights::Ball* SexyNights::Ball::ball;

static SexyNights::Ball* (__fastcall* SexyNights__Ball__Ball_)(SexyNights::Ball*, char*, bool);
SexyNights::Ball* __fastcall SexyNights__Ball__Ball(SexyNights::Ball* this_, char* edx, bool a2)
{
	SexyNights::Ball::ball = this_;
	return SexyNights__Ball__Ball_(this_, edx, a2);
}

void SexyNights::Ball::setup()
{

}

bool SexyNights::Ball::check_exists()
{
	if (SexyNights::Ball::ball == 0x0) return false;
	return true;
}
