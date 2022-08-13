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
	enum class PowerupType : std::int32_t
	{
		None = 0,
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
		// Nights-only
		Electrobolt,
		AIPlayerControl,
	};

	// This enum contains the characters' name or the type of animal they represent.
	// Both are valid (e.g. `Bjorn == Unicorn`).
	enum class CharacterId : std::int32_t
	{
		Bjorn = 0, Unicorn = 0,
		JimmyLightning = 1, Gopher = 1,
		Kat = 2, Cat = 2,
		Splork = 3, Alien = 3,
		Claude = 4, Lobster = 4,
		Renfield = 5, Pumpkin = 5,
		Tula = 6, Sunflower = 6,
		Warren = 7, Rabbit = 7,
		LordCinderbottom = 8, Dragon = 8,
		MasterHu = 9, Owl = 9,
		// Nights-only
		Marina = 10, Squid = 10,

	};

	enum class PlayerId : std::int32_t
	{
		Player_1 = 0,
		Player_2 = 1,

		MAX_PLAYER_COUNT  // Keep this always last to automatically count the maximum number of players.
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
			CharacterSelect = 9,
			ZenBall = 10
		};

		#pragma pack(1)  // Force compiler to pack struct in single bytes.
		struct LogicMgr_Deluxe101_
		{
			int unk;
			int state;
			int state_0;
			char data[916];
		};

		#pragma pack(1)  // Force compiler to pack struct in single bytes.
		struct LogicMgr_Nights101_
		{
			std::int32_t* unk_0;  // vtable
			LogicMgr::State state;
			std::int32_t shotTimer;
			std::uint8_t unk_1[0x4c - 0x08 - sizeof shotTimer];
			std::int32_t numOrangePegsHitThisShot;
			std::int32_t numGreenPegsHitThisShot;
			std::uint8_t unk_2[0xEC - 0x50 - sizeof numGreenPegsHitThisShot];
			float gunAngleRadians;
			std::uint8_t unk_3[0x1AC - 0x0EC - sizeof gunAngleRadians];
			PlayerId playerCurrentlyInControl;
			std::uint8_t unk_4[0x200 - 0x1AC - sizeof playerCurrentlyInControl];
			// Begin player data
			std::int32_t playerScore[static_cast<int>(PlayerId::MAX_PLAYER_COUNT)];
			std::int32_t playerRemainingBallCount[static_cast<int>(PlayerId::MAX_PLAYER_COUNT)];
			CharacterId playerCharacter[static_cast<int>(PlayerId::MAX_PLAYER_COUNT)];
			#pragma pack(1)
			struct PlayerNameDataType
			{
				std::uint32_t unk_0;
				static constexpr std::int32_t NAME_STRING_LENGTH = 16;  ///< Use this to make sure you don't read or write outside of the char array.
				char nameString[NAME_STRING_LENGTH];
				std::int32_t nameLength;
				std::uint32_t nameMaximumLength;
			} playerNameData[static_cast<int>(PlayerId::MAX_PLAYER_COUNT)];
			PowerupType playerMainPowerup[static_cast<int>(PlayerId::MAX_PLAYER_COUNT)];  // This is usually determined by which character the player selects.
			std::uint8_t unk_5[0x270 - 0x25C - sizeof playerMainPowerup[0]];
			std::int32_t playerSuperGuideUsesRemaining[static_cast<int>(PlayerId::MAX_PLAYER_COUNT)];
			std::int32_t playerFlipperTurnsRemaining[static_cast<int>(PlayerId::MAX_PLAYER_COUNT)];
			std::int32_t unk_6[static_cast<int>(PlayerId::MAX_PLAYER_COUNT)];
			std::int32_t playerPyramidTurnsRemaining[static_cast<int>(PlayerId::MAX_PLAYER_COUNT)];
			std::int32_t unk_7[static_cast<int>(PlayerId::MAX_PLAYER_COUNT)];
			std::int32_t playerSpookyBallUsesRemaining[static_cast<int>(PlayerId::MAX_PLAYER_COUNT)];
			std::int32_t playerZenShotUsesRemaining[static_cast<int>(PlayerId::MAX_PLAYER_COUNT)];
			std::uint8_t unk_8[0x2C8 - 0x2A4 - sizeof playerZenShotUsesRemaining[0]];
			std::int32_t playerFireballUsesRemaining[static_cast<int>(PlayerId::MAX_PLAYER_COUNT)];
			std::int32_t unk_9[static_cast<int>(PlayerId::MAX_PLAYER_COUNT)];
			std::int32_t playerElectroboltUsesRemaining[static_cast<int>(PlayerId::MAX_PLAYER_COUNT)];
			std::int32_t unk_10;
			#pragma pack(1)
			struct PlayerShotDataType
			{
				std::int32_t numShotsTaken;
				std::int32_t highPegScore;  // Does not include Style points.
				std::int32_t feverScore;
				// Free ball counters
				std::int32_t bucketFreeBallCount;
				std::int32_t megaShotT1FreeBallCount;  // 25,000 shot score
				std::int32_t megaShotT2FreeBallCount;  // 75,000 shot score
				std::int32_t megaShotT3FreeBallCount;  // 125,000 shot score
				// Style shot counters (see Peggle's readme for descriptions)
				std::int32_t longShotCount;
				std::int32_t unk_0;
				std::int32_t extremeSlideCount;
				std::int32_t orangeAttackCount;
				std::uint8_t unk_1[0x324 - 0x30C - sizeof orangeAttackCount];
				std::int32_t freeBallSkillsCount;
				std::uint8_t unk_2[0x330 - 0x324 - sizeof freeBallSkillsCount];
				std::int32_t luckyBounceCount;
				std::int32_t madSkillzCount;
				std::uint8_t unk_3[0x344 - 0x334 - sizeof madSkillzCount];
				std::int32_t duelBucketBonusCount;
				std::int32_t duelLuckyBounceCount;
				std::int32_t duelMegaShotBonusCount;
				std::uint8_t unk_4[0x360 - 0x34C - sizeof duelMegaShotBonusCount];
			} playerShotData[static_cast<int>(PlayerId::MAX_PLAYER_COUNT)];
			std::uint8_t unk_11[0x3EC - 0x3C8 - sizeof PlayerShotDataType::unk_4 - sizeof PlayerShotDataType::duelMegaShotBonusCount];
			// The "peg remover" is the effect when a shot ends and the hit pegs get removed one at a time in a trailing path.
			std::int32_t pegRemoverPositionX;
			std::int32_t pegRemoverPositionY;
			std::int32_t ballPositionX;
			std::int32_t ballPositionY;
			std::uint8_t unk_12[0x41C - 0x3F8 - sizeof ballPositionY];
			std::int32_t numOrangePegsRemainingInStage;
			std::int32_t* electroboltPreShotHitAnticipationTargetPegPtr;  // When Marina's Electrobolt power-up is active, the peg in the direct line-of-sight of the gun will be given an electricity VFX before the shot is taken. This seems to be the only power-up that applies a VFX like this.
			char data[916];
		};

		static LogicMgr* logic_mgr;
		static void setup();

		static Sexy::LogicMgr* IncNumBalls(int top_count, int bottom_count, bool bottom);
		static int BeginShot(bool doGetReplayPoint);
		static void MouseDown(int xPos, int yPos, int mouseButtonId, bool b1, bool b2);
		static void DoPowerup(Sexy::Ball* ball, Sexy::PhysObj* phys_obj, int powerup, int a5);
		static void ActivateFreeBallCover(int a2);
		static void ActivatePowerup(int powerup, int a3);
		static std::int64_t DoMultiball(Sexy::Ball* a2, Sexy::PhysObj* a3);
		static void PegHit(Sexy::Ball* ball, Sexy::PhysObj* phys_obj, bool a4);
		static void DoExploder(Sexy::Ball* ball, Sexy::PhysObj* phys_obj);
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
		static float RadiansToDegrees(float angleRadians);
		static Sexy::FloatingText* AddStandardText(const std::string& string, float pos_x, float pos_y, int type);
		static Sexy::FloatingText* AddStandardText(const char* string, float pos_x, float pos_y, int type); //overload for cstring
		static void CalcCornerDisplay();

	private:
		static bool check_exists();
		static bool TryPointerRefresh(void);
		static void SetGunAngle(float newAngleDegrees);
	};
}
