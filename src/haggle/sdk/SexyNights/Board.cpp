#include "Board.hpp"
#include "callbacks/callbacks.hpp"

SexyNights::Board* SexyNights::Board::board;

static char* (__fastcall* SexyNights__Board__Board_)(SexyNights::Board*, char*, char*);
char* __fastcall SexyNights__Board__Board(SexyNights::Board* this_, char* edx, char* thunderball)
{
	SexyNights::Board::board = this_;
	return SexyNights__Board__Board_(this_, edx, thunderball);
}

void SexyNights::Board::setup()
{

}

bool SexyNights::Board::check_exists()
{
	if (SexyNights::Board::board == 0x0) return false;
	return true;
}
