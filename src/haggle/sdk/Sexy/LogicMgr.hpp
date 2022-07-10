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
		static int BeginShot(bool doGetReplayPoint);
		static void MouseDown(int xPos, int yPos, int mouseButtonId, bool b1, bool b2);
		static void DoPowerup(Sexy::Ball* ball, Sexy::PhysObj* phys_obj, int powerup, int a5);
		static void ActivatePowerup(int powerup, int a3);
		static std::int64_t DoMultiball(Sexy::Ball* a2, Sexy::PhysObj* a3);
		static void PegHit(Sexy::Ball* ball, Sexy::PhysObj* phys_obj, bool a4);
		static void DoExploder(Sexy::Ball* ball, Sexy::PhysObj* phys_obj);
		static bool BeginTurn2();
		static int SetState(int a2);
		static void ActivateFreeBall(bool a4);
		static void SetWearHat(int a2);
		static void SetGunAngle(float newAngleRadians);

		/** @brief Converts degrees to radians normalized to the gun's coordinate system.
		* 
		 * @details
		 * 0 degrees == down
		 * 90 degrees == right
		 * -90 degrees == left
		 *
		 * The available degree range is restricted by +/-`ANGLE_CONSTRAINT` where
		 * `ANGLE_CONSTRAINT = (180 - Sexy::GetAngleConstraint())` (`Sexy::GetAngleConstraint()` defaults to 83.0 degrees) from 0 degrees.
		 * Therefore, the default range of degrees is -97.0 to +97.0.
		 * Any values outside of this range will cause `Sexy::LogicMgr::SetGunAngle()` to clip the input angle to one of the limits.
		 *
		 * Very detailed note: The gun uses a standard <a href="https://en.wikipedia.org/wiki/Polar_coordinate_system">polar coordinate system</a>,
		 * where 0 degrees is to the right. Straight down is 270 degrees. Therefore, this function automatically normalizes the input angle so
		 * that the coordinate system is rotated +270 degrees. `Sexy::GetAngleConstraint()` defaults to 83.0 degrees, and from the gun's coordinate
		 * system, the constraint is applied to 90 (straight up). Angles in this range (default: 7 to 173) are inaccessible for the gun.
		 * The coordinate system rotation that is automatically applied puts 0 degrees directly in the middle of the accessible range. Straight up
		 * is 180 degrees away, so that is why the available range has to be calculated as `+/-(180 - Sexy::GetAngleConstraint())`.
		 */
		static float DegreesToRadians(float angleDegrees);
		static Sexy::FloatingText* AddStandardText(std::string string, float pos_x, float pos_y, int type);
		static Sexy::FloatingText* AddStandardText(const char* string, float pos_x, float pos_y, int type); //overload for cstring

	private:
		static bool check_exists();
	};
}
