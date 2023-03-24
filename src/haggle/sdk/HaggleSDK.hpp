#pragma once

class __declspec(dllexport) Haggle
{
public:
	enum class PeggleVersion : int
	{
		Unknown = -1,
		Deluxe101,
		NightsDeluxe10
	};

	static PeggleVersion version;
};
