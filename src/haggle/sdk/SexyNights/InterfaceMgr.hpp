#pragma once

#include "Board.hpp"

//Size: 372
namespace SexyNights
{
	class __declspec(dllexport) InterfaceMgr
	{
	public:
		static InterfaceMgr* interface_mgr;
		static void setup();
		static bool check_exists();
		
		static SexyNights::InterfaceMgr* UpdateBalls();

		static SexyNights::InterfaceMgr* LoadGun();
		//Overload that uses this
		static SexyNights::InterfaceMgr* AddTopBalls(int count);
		static SexyNights::InterfaceMgr* AddTopBalls(SexyNights::InterfaceMgr* input, int count);
		static SexyNights::InterfaceMgr* SetNumBalls(int count);
		static SexyNights::InterfaceMgr* SetNumBalls(SexyNights::InterfaceMgr* input, int count);
	};
};
