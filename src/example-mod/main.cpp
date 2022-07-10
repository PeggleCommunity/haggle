#include "sdk/SexySDK.hpp"

HMODULE self = 0;

void init()
{
	bool shutdown = false;
	float anglesInDegrees[] = { 0.0f, -30.0f, 60.0f };
	enum class PointingDirections
	{
		DOWN = 0,
		LEFT = 1,
		RIGHT = 2
	};
	PointingDirections pointDirection = PointingDirections::DOWN;

	//Select which modules you will be using, do not activate all if
	//you do not need them for saftey and efficency
	//
	//For the example mod, we are only using Sexy::LogicMgr and Sexy::SoundMgr
	//(to show text and play a sound)

	if(MH_Initialize() == MH_OK);
	{
		Sexy::Board::setup();
		Sexy::LogicMgr::setup();
		//Sexy::Ball::setup();
		//Sexy::PhysObj::setup();
		Sexy::SoundMgr::setup();
		//Sexy::CharacterMgr::setup();
		//Sexy::EffectMgr::setup();
		//Sexy::CollisionMgr::setup();
		//Sexy::InterfaceMgr::setup();

		MH_EnableHook(MH_ALL_HOOKS);
	}

	//Example Mod stuff
	while (true)
	{
		//Most of the stuff will only call if you are in game
		//and have allocated the proper memory for usage
		//
		//Inject in main menu and load a board, don't inject mid-game,
		//it will not have the required data to activate the mod sdk

		float newAngleInDegrees = anglesInDegrees[static_cast<int>(PointingDirections::DOWN)];
		switch (pointDirection)
		{
			case PointingDirections::DOWN:
			{
				newAngleInDegrees = anglesInDegrees[static_cast<int>(pointDirection)];
				Sexy::LogicMgr::AddStandardText(std::string("DOWN!"), 330.0f, 200.0f, 48);	//Shows text
				pointDirection = PointingDirections::LEFT;
				break;
			}
			case PointingDirections::LEFT:
			{
				newAngleInDegrees = anglesInDegrees[static_cast<int>(pointDirection)];
				Sexy::LogicMgr::AddStandardText(std::string("LEFT!"), 330.0f, 200.0f, 48);	//Shows text
				pointDirection = PointingDirections::RIGHT;
				break;
			}
			case PointingDirections::RIGHT:
			{
				newAngleInDegrees = anglesInDegrees[static_cast<int>(pointDirection)];
				Sexy::LogicMgr::AddStandardText(std::string("RIGHT!"), 330.0f, 200.0f, 48);	//Shows text
				pointDirection = PointingDirections::DOWN;
				break;
			}
			default:
			{
				break;
			}
		}

		Sexy::LogicMgr::SetGunAngle(Sexy::LogicMgr::DegreesToRadians(newAngleInDegrees));
		Sleep(1 * 1000);  // Sleep for a bit to allow the game to handle the new gun angle.
		Sexy::LogicMgr::MouseDown(100, 100, 1, false, false);
		// Sexy::Board::KeyDown(0x0D);  // Simulate pressing the enter key (key code 0x0D) to shoot the ball.

		Sleep(20 * 1000);
	}

	FreeLibraryAndExitThread(self, 0);
}

DWORD WINAPI OnAttachImpl(LPVOID lpParameter)
{
	init();
	return 0;
}

DWORD WINAPI OnAttach(LPVOID lpParameter)
{
	__try
	{
		return OnAttachImpl(lpParameter);
	}
	__except (0)
	{
		FreeLibraryAndExitThread((HMODULE)lpParameter, 0xDECEA5ED);
	}

	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		self = hModule;
		DisableThreadLibraryCalls(self);
		CreateThread(nullptr, 0, OnAttach, self, 0, nullptr);
		return true;
	}

	return false;
}
