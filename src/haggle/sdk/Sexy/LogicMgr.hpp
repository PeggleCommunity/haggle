#pragma once

#include "Board.hpp"
#include "Ball.hpp"
#include "PhysObj.hpp"
#include "SoundMgr.hpp"
#include "EffectMgr.hpp"
#include "FloatingText.hpp"

//Size: 924
namespace Sexy
{
	enum PowerUp : int
	{
		None,
		SuperGuide,
		Flippers,
		Multiball,
		Pyramid,
		SpaceBlast,
		SpookyBall,
		ZenShot,
		ShotExtender,
		FlowerPower,
		Nudge,
		TimeBomb,
		FireBall,
		LuckySpin,
	};

	struct LogicMgr_
	{
		int unk;
		int state;
		int state_0;
		char data[916];
	};

	class LogicMgr
	{
	public:
		static LogicMgr* logic_mgr;
		static void setup();

		static Sexy::LogicMgr* IncNumBalls(int top_count, int bottom_count, bool bottom);
		static int BeginShot(bool a2);
		static void DoPowerup(Sexy::Ball* ball, Sexy::PhysObj* phys_obj, int powerup, int a5);
		static void ActivatePowerup(int powerup, int a3);
		static std::int64_t DoMultiball(Sexy::Ball* a2, Sexy::PhysObj* a3);
		static void PegHit(Sexy::Ball* ball, Sexy::PhysObj* phys_obj, bool a4);
		static void DoExploder(Sexy::Ball* ball, Sexy::PhysObj* phys_obj);
		static bool BeginTurn2();
		static int SetState(int a2);
		static void ActivateFreeBall(bool a4);
		static void SetWearHat(int a2);
		static void SetGunAngle(float newAngle);
		static Sexy::FloatingText* AddStandardText(std::string string, float pos_x, float pos_y, int type);
		static Sexy::FloatingText* AddStandardText(const char* string, float pos_x, float pos_y, int type); //overload for cstring

	private:
		static bool check_exists();
	};
}
