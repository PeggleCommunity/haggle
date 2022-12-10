#include "sdk/SexySDK.hpp"
#include "callbacks/callbacks.hpp"

HMODULE self = 0;
PeggleVersion version = PeggleVersion::Unknown;

void init()
{
	if (!strcmp(reinterpret_cast<char*>(0x005D675C), "Peggle Deluxe "))
	{
		version = PeggleVersion::Deluxe101;
		std::printf("[ HAGGLE ]: Detected Peggle Deluxe 1.01\n");
	}
	else if (!strcmp(reinterpret_cast<char*>(0x006851D0), "Peggle Nights"))
	{
		version = PeggleVersion::NightsDeluxe10;
		std::printf("[ HAGGLE ]: Detected Peggle Nights Deluxe 1.0\n");
	}
	else
	{
		version = PeggleVersion::Unknown;
		std::printf("[ HAGGLE ]: Unable to detect game!\n");
	}

	if (MH_Initialize() == MH_OK);
	{
		callbacks::init();	//Although not related to minhook starting, its useless without it

		Sexy::ThunderballApp::setup();
		Sexy::Board::setup();
		Sexy::LogicMgr::setup();
		Sexy::Ball::setup();
		Sexy::PhysObj::setup();
		Sexy::SoundMgr::setup();
		Sexy::CharacterMgr::setup();
		Sexy::EffectMgr::setup();
		Sexy::CollisionMgr::setup();
		Sexy::InterfaceMgr::setup();
		Sexy::PlayerInfo::setup();
		Sexy::LevelScreen::setup();
		Sexy::StageMgr::setup();
		Sexy::MainMenu::setup();
		Sexy::Graphics::setup();

		MH_EnableHook(MH_ALL_HOOKS);
	}
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
