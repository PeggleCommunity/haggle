#include <random>
#include "sdk/SexySDK.hpp"
#include "callbacks/callbacks.hpp"

HMODULE self = 0;

void Example_Callbacks(void);
void Example_AutoShoot(void);

void init()
{
	// Example Mod stuff

	Example_Callbacks();
	Example_AutoShoot();
}

void Example_Callbacks(void)
{
	// Example generic callback
	callbacks::on(callbacks::type::begin_turn_2, []()
	{
		Sexy::LogicMgr::AddStandardText("Begin Turn!", 330.0f, 150.0f, 48);
	});

	callbacks::on_begin_shot([](auto logic_mgr, auto a2)
	{
		Sexy::LogicMgr::AddStandardText("Shoot!", 100.0f, 25.0f, 48);
	});

	// Example callback for peg hit
	callbacks::on_peg_hit([](auto ball, auto phys_obj, auto a4)
	{
		Sexy::PhysObj_* phys_obj_ = (Sexy::PhysObj_*)phys_obj;
		double pos_x = ((double(__thiscall*)(Sexy::PhysObj*)) * (std::uint32_t*)(*(std::uint32_t*)phys_obj_->data + 120))(phys_obj);
		double pos_y = ((double(__thiscall*)(Sexy::PhysObj*)) * (std::uint32_t*)(*(std::uint32_t*)phys_obj_->data + 124))(phys_obj);
		Sexy::LogicMgr::AddStandardText("Peg Hit!", pos_x, pos_y, 50);
	});

	callbacks::on_load_level([](auto board, auto level_name)
	{
		std::printf("Loading Level: %s\n", level_name.c_str());
	});

	callbacks::on_do_play([](auto level_screen, auto a3)
	{
		// this is pretty disgusting, but this is what we have until we map out the struct
		uint32_t stage = *(uint32_t*)(&level_screen + 651) + 1;  // offset to stage index
		uint32_t level = *(uint32_t*)(&level_screen + 652) + 1;  // offset to level index
		std::printf("Loading Level: %d-%d\n", stage, level);
	});
}

/** @brief Swings the gun left and right, and shoots whenever the game is ready
 * for the player to shoot.
 */
void Example_AutoShoot(void)
{
	callbacks::on(callbacks::type::main_loop, []()
	{
		static float angleIncrement = 8.0f;
		static constexpr int MOVE_DELAY_MS = 1000 / 60;
		static constexpr float ANGLE_BOUNDS[] = { -93.0f, 93.0f };
		static bool isMovingLeft = false;

		static std::random_device rd;  //Will be used to obtain a seed for the random number engine
		static std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		static std::uniform_int_distribution<> distribDelayMs(1000, 2000);
		static unsigned int firstShotDelayCounter = 0;
		static unsigned int firstShotDelayMs = distribDelayMs(gen);

		Sexy::LogicMgr::State logicState = Sexy::LogicMgr::GetState();
		switch (logicState)
		{
		case Sexy::LogicMgr::State::PreShot:
		case Sexy::LogicMgr::State::Shot:
		case Sexy::LogicMgr::State::PostShot:
		case Sexy::LogicMgr::State::TotalMiss:
		case Sexy::LogicMgr::State::PostPostShot:
		case Sexy::LogicMgr::State::ShotExtender:
		case Sexy::LogicMgr::State::ZenBall:
			break;
		default:
			firstShotDelayCounter = 0;  // Since we're not in a playing state, reset the delayed first shot counter.
			return;
		}

		float currentGunAngleDegrees = Sexy::LogicMgr::GetGunAngleDegrees();
		if (isMovingLeft)
		{
			if (currentGunAngleDegrees - angleIncrement < ANGLE_BOUNDS[0])
			{
				isMovingLeft = false;
				currentGunAngleDegrees += angleIncrement;
			}
			else
			{
				currentGunAngleDegrees -= angleIncrement;
			}
		}
		else
		{
			if (currentGunAngleDegrees + angleIncrement > ANGLE_BOUNDS[1])
			{
				isMovingLeft = true;
				currentGunAngleDegrees -= angleIncrement;
			}
			else
			{
				currentGunAngleDegrees += angleIncrement;
			}
		}

		Sexy::LogicMgr::SetGunAngleDegrees(currentGunAngleDegrees);
		if (logicState == Sexy::LogicMgr::State::PreShot)
		{
			if (firstShotDelayCounter >= firstShotDelayMs)
			{
				Sexy::LogicMgr::MouseDown(100, 100, 1, false, false);
			}
			else
			{
				firstShotDelayCounter += MOVE_DELAY_MS;
			}
		}
	});
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
