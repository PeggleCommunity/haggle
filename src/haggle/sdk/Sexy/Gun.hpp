#pragma once

namespace Sexy
{
	class Board;
	class DataSync;

	class __declspec(dllexport) Gun
	{
	public:
		static Gun* gun;

		static void setup();
		static bool check_exists();

		void SyncState(DataSync* sync);
		void SetDoBouncyGuide(bool doBouncyGuide);
	};
}
