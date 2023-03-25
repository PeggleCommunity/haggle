#pragma once

#include "Board.hpp"
#include "Ball.hpp"
#include "PhysObj.hpp"
#include "SoundMgr.hpp"
#include "EffectMgr.hpp"
#include "FloatingText.hpp"

//Size: 1108
namespace SexyNights
{
	enum PowerupType : int
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

	class __declspec(dllexport) LogicMgr
	{
	public:
		enum class State : int
		{
			None = 0,
			PreShot = 1,
			Shot = 2,
			PostShot = 3,
			TotalMiss = 4,
			LevelDone = 5,
			PostPostShot = 6,
			ShotExtender = 7,
			InitLevel = 8,
			CharacterDialog = 9,
			ZenBall = 10
		};

		static LogicMgr* logic_mgr;
		static void setup();

		static SexyNights::LogicMgr* IncNumBalls(int top_count, int bottom_count, bool bottom);
		static int BeginShot(bool doGetReplayPoint);
		static void MouseDown(int xPos, int yPos, int mouseButtonId, bool b1, bool b2);
		static void DoPowerup(SexyNights::Ball* ball, SexyNights::PhysObj* phys_obj, int powerup, int a5);
		static void ActivateFreeBallCover(int a2);
		static void ActivatePowerup(int powerup, int a3);
		static std::int64_t DoMultiball(SexyNights::Ball* a2, SexyNights::PhysObj* a3);
		static void PegHit(SexyNights::Ball* ball, SexyNights::PhysObj* phys_obj, bool a4);
		static void DoExploder(SexyNights::Ball* ball, SexyNights::PhysObj* phys_obj);
		static bool BeginTurn2();
		static void SetState(State newState);
		static State GetState(void);
		static void ActivateFreeBall(bool a4);
		static void SetWearHat(int a2);
		static void SetGunAngleRadians(float newAngleRadians);
		static void SetGunAngleDegrees(float newAngleDegrees);
		static float GetGunAngleRadians(void);
		static float GetGunAngleDegrees(void);

		/** @brief Converts degrees to radians normalized to the gun's coordinate system.
		*
		 * @details
		 * 0 degrees == down
		 * 90 degrees == right
		 * -90 degrees == left
		 *
		 * The available degree range is restricted by +/-`ANGLE_CONSTRAINT` where
		 * `ANGLE_CONSTRAINT = (180 - SexyNights::GetAngleConstraint())` (`SexyNights::GetAngleConstraint()` defaults to 83.0 degrees) from 0 degrees.
		 * Therefore, the default range of degrees is -97.0 to +97.0.
		 * Any values outside of this range will cause `SexyNights::LogicMgr::SetGunAngle()` to clip the input angle to one of the limits.
		 *
		 * Very detailed note: The gun uses a standard <a href="https://en.wikipedia.org/wiki/Polar_coordinate_system">polar coordinate system</a>,
		 * where 0 degrees is to the right. Straight down is 270 degrees. Therefore, this function automatically normalizes the input angle so
		 * that the coordinate system is rotated +270 degrees. `SexyNights::GetAngleConstraint()` defaults to 83.0 degrees, and from the gun's coordinate
		 * system, the constraint is applied to 90 (straight up). Angles in this range (default: 7 to 173) are inaccessible for the gun.
		 * The coordinate system rotation that is automatically applied puts 0 degrees directly in the middle of the accessible range. Straight up
		 * is 180 degrees away, so that is why the available range has to be calculated as `+/-(180 - SexyNights::GetAngleConstraint())`.
		 */
		static float DegreesToRadians(float angleDegrees);
		static float RadiansToDegrees(float angleRadians);
		static SexyNights::FloatingText* AddStandardText(std::string& string, float pos_x, float pos_y, int type);
		static void CalcCornerDisplay();

	private:
		static bool check_exists();
		static void SetGunAngle(float newAngleDegrees);
	};

	struct LogicMgr_
	{
		int unk;
		SexyNights::LogicMgr::State state;
		int state_0;
		char padding_0[280];
		bool is_duel;
		char padding_1[635];
	};
}
