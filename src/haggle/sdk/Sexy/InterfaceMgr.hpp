#pragma once

#include "Board.hpp"

//Size: 372
namespace Sexy
{
	class __declspec(dllexport) InterfaceMgr
	{
	public:
		static InterfaceMgr* interface_mgr;
		static void setup();
		static bool check_exists();
		
		static Sexy::InterfaceMgr* UpdateBalls();

		static Sexy::InterfaceMgr* LoadGun(Sexy::InterfaceMgr* input = Sexy::InterfaceMgr::interface_mgr);
		//Overload that uses this
		static Sexy::InterfaceMgr* AddTopBalls(int count);
		static Sexy::InterfaceMgr* AddTopBalls(Sexy::InterfaceMgr* input, int count);
		static Sexy::InterfaceMgr* SetNumBalls(int count);
		static Sexy::InterfaceMgr* SetNumBalls(Sexy::InterfaceMgr* input, int count);
	};
};
