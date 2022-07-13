#include <random>
#include "sdk/SexySDK.hpp"
#include "callbacks/callbacks.hpp"

HMODULE self = 0;

void Example_0(void);
void Example_1(void);

void init()
{
	// Example Mod stuff
	callbacks::on_peg_hit([](Sexy::Ball* ball, Sexy::PhysObj* phys_obj, bool a4)
	{
		Sexy::PhysObj_* phys_obj_ = (Sexy::PhysObj_*)phys_obj;
		double pos_x = ((double(__thiscall*)(Sexy::PhysObj*)) * (std::uint32_t*)(*(std::uint32_t*)phys_obj_->data + 120))(phys_obj);
		double pos_y = ((double(__thiscall*)(Sexy::PhysObj*)) * (std::uint32_t*)(*(std::uint32_t*)phys_obj_->data + 124))(phys_obj);
		Sexy::LogicMgr::AddStandardText("Peg Hit!", pos_x, pos_y, 50);
	});

	// Example_0();
	Example_1();


	FreeLibraryAndExitThread(self, 0);
}


/** @brief After a delay, sets the gun to a certain angle and shoots the ball.
 * This continues on to the next angle out of three total angles, and loops back
 * to the first angle after all three angles have been used.
 */
void Example_0(void)
{
	float anglesInDegrees[] = { 0.0f, -30.0f, 60.0f };
	enum class PointingDirections
	{
		DOWN = 0,
		LEFT = 1,
		RIGHT = 2
	};
	PointingDirections pointDirection = PointingDirections::DOWN;

	//Select which modules you will be using, do not activate all if
	//you do not need them for saftey and efficiency
	if (MH_Initialize() == MH_OK);
	{
		Sexy::Board::setup();
		Sexy::LogicMgr::setup();
		// Sexy::Ball::setup();
		// Sexy::PhysObj::setup();
		// Sexy::SoundMgr::setup();
		// Sexy::CharacterMgr::setup();
		// Sexy::EffectMgr::setup();
		// Sexy::CollisionMgr::setup();
		// Sexy::InterfaceMgr::setup();

		MH_EnableHook(MH_ALL_HOOKS);
	}

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

		Sexy::LogicMgr::SetGunAngleDegrees(newAngleInDegrees);
		Sleep(1 * 1000);  // Sleep for a bit to allow the game to handle the new gun angle.
		Sexy::LogicMgr::MouseDown(100, 100, 1, false, false);
		// Sexy::Board::KeyDown(0x0D);  // Simulate pressing the enter key (key code 0x0D) to shoot the ball.

		Sleep(20 * 1000);
	}
}

/** @brief Swings the gun left and right, and shoots whenever the game is ready
 * for the player to shoot.
 */
void Example_1(void)
{
	float angleIncrement = 8.0f;
	constexpr int MOVE_DELAY_MS = 1000 / 60;
	constexpr float ANGLE_BOUNDS[] = { -93.0f, 93.0f };
	bool isMovingLeft = false;

	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distribDelayMs(1000, 2000);
	unsigned int firstShotDelayCounter = 0;
	unsigned int firstShotDelayMs = distribDelayMs(gen);

	//Select which modules you will be using, do not activate all if
	//you do not need them for saftey and efficiency
	if (MH_Initialize() == MH_OK);
	{
		Sexy::Board::setup();
		Sexy::LogicMgr::setup();
		// Sexy::Ball::setup();
		// Sexy::PhysObj::setup();
		// Sexy::SoundMgr::setup();
		// Sexy::CharacterMgr::setup();
		// Sexy::EffectMgr::setup();
		// Sexy::CollisionMgr::setup();
		// Sexy::InterfaceMgr::setup();

		MH_EnableHook(MH_ALL_HOOKS);
	}

	while (true)
	{
		//Most of the stuff will only call if you are in game
		//and have allocated the proper memory for usage
		//
		//Inject in main menu and load a board, don't inject mid-game,
		//it will not have the required data to activate the mod sdk
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
			continue;
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

		Sleep(MOVE_DELAY_MS);
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
