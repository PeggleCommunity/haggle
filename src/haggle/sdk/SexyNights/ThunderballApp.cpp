#include "ThunderballApp.hpp"
#include "callbacks/callbacks.hpp"

//For implementation later
SexyNights::ThunderballApp* SexyNights::ThunderballApp::thunderball /*= *reinterpret_cast<SexyNights::ThunderballApp**>(0x00687394)*/;

void SexyNights::ThunderballApp::setup()
{

}

bool SexyNights::ThunderballApp::check_exists()
{
	if (SexyNights::ThunderballApp::thunderball == 0x0) return false;
	return true;
}
