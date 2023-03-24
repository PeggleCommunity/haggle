#include "PhysObj.hpp"

float& SexyNights::PhysObj::mGravity = *reinterpret_cast<float*>(0x00649D80);

static SexyNights::PhysObj(__fastcall* SexyNights__PhysObj__PhysObj_)(SexyNights::PhysObj*, char*);
SexyNights::PhysObj __fastcall SexyNights__PhysObj__PhysObj(SexyNights::PhysObj* this_, char* edx)
{
	return SexyNights__PhysObj__PhysObj_(this_, edx);
}

void SexyNights::PhysObj::setup()
{

}

bool SexyNights::PhysObj::check_exists()
{
	return true;
}
