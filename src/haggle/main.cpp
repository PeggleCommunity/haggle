#include "sdk/SexySDK.hpp"
#include "sdk/SexyNightsSDK.hpp"
#include "sdk/HaggleSDK.hpp"
#include "sdk/Sexy/callbacks/callbacks.hpp"

HMODULE self = 0;
Haggle::PeggleVersion Haggle::version = Haggle::PeggleVersion::Unknown;

void init()
{
	Haggle::version = Haggle::get_game_version();

	if (MH_Initialize() == MH_OK);
	{
		switch (Haggle::version)
		{
			case Haggle::PeggleVersion::Deluxe101:
			{
				Sexy::callbacks::init();

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
			} break;

			case Haggle::PeggleVersion::NightsDeluxe10:
			{
				SexyNights::ThunderballApp::setup();
				SexyNights::Board::setup();
				SexyNights::LogicMgr::setup();
				SexyNights::Ball::setup();
				SexyNights::PhysObj::setup();
				SexyNights::SoundMgr::setup();
				SexyNights::CharacterMgr::setup();
				SexyNights::EffectMgr::setup();
				SexyNights::CollisionMgr::setup();
				SexyNights::InterfaceMgr::setup();
				SexyNights::PlayerInfo::setup();
				SexyNights::LevelScreen::setup();
				SexyNights::StageMgr::setup();
				SexyNights::MainMenu::setup();
				SexyNights::Graphics::setup();
			} break;
		}

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
