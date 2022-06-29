#include "sdk/SexySDK.hpp"

HMODULE self = 0;

void init()
{
	bool shutdown = false;
	int count = 10;

	//Select which modules you will be using, do not activate all if
	//you do not need them for saftey and efficency
	//
	//For the example mod, we are only using Sexy::LogicMgr and Sexy::SoundMgr
	//(to show text and play a sound)

	if(MH_Initialize() == MH_OK);
	{
		//Sexy::Board::setup();
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
	while (!shutdown)
	{
		//Most of the stuff will only call if you are in game
		//and have allocated the proper memory for usage
		//
		//Inject in main menu and load a board, don't inject mid-game,
		//it will not have the required data to activate the mod sdk

		Sexy::SoundMgr::AddSound(Sexy::SOUND_AAH, 0.0f, 0, 1, 1, -1.0f);						//Plays a sound
		Sexy::LogicMgr::AddStandardText(std::string("Haggle Mod SDK!"), 330.0f, 200.0f, 48);	//Shows text
		--count;

		if (count <= 0)
		{
			shutdown = true;
		}

		Sleep(10000);
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
