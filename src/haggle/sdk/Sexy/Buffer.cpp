#include "Buffer.hpp"

namespace Sexy
{
	Buffer::Buffer()
	{
		reinterpret_cast<void(__thiscall*)(Buffer*)>(0x0050f220)(this);
	}

	Buffer::~Buffer()
	{
		reinterpret_cast<void(__thiscall*)(Buffer*)>(0x00501020)(this);
	}

	std::string Buffer::ToWebString() const
	{
		return reinterpret_cast<std::string(__thiscall*)(const Buffer*)>(0x00501f60)(this);
	}

	std::wstring Buffer::UTF8ToWideString() const
	{
		return reinterpret_cast<std::wstring(__thiscall*)(const Buffer*)>(0x00503590)(this);
	}

	void Buffer::SeekFront() const
	{
		reinterpret_cast<void(__thiscall*)(const Buffer*)>(0x004fbd20)(this);
	}

	void Buffer::Clear()
	{
		reinterpret_cast<void(__thiscall*)(Buffer*)>(0x00501f90)(this);
	}

	void Buffer::WriteByte(uchar theByte)
	{
		reinterpret_cast<void(__thiscall*)(Buffer*, uchar)>(0x005119f0)(this, theByte);
	}

	void Buffer::WriteNumBits(int theNum, int theBits)
	{
		reinterpret_cast<void(__thiscall*)(Buffer*, int, int)>(0x00511a90)(this, theNum, theBits);
	}

	void Buffer::WriteBoolean(bool theBool)
	{
		reinterpret_cast<void(__thiscall*)(Buffer*, bool)>(0x00511b90)(this, theBool);
	}

	void Buffer::WriteShort(short theShort)
	{
		reinterpret_cast<void(__thiscall*)(Buffer*, short)>(0x00511bb0)(this, theShort);
	}

	void Buffer::WriteLong(long theLong)
	{
		reinterpret_cast<void(__thiscall*)(Buffer*, long)>(0x00511be0)(this, theLong);
	}

	void Buffer::WriteString(const std::string& theString)
	{
		reinterpret_cast<void(__thiscall*)(Buffer*, const std::string&)>(0x00511c20)(this, theString);
	}

	void Buffer::WriteLine(const std::string& theString)
	{
		reinterpret_cast<void(__thiscall*)(Buffer*, const std::string&)>(0x005169b0)(this, theString);
	}

	void Buffer::WriteBytes(const uchar* theByte, int theCount)
	{
		reinterpret_cast<void(__thiscall*)(Buffer*, const uchar*, int)>(0x00511c80)(this, theByte, theCount);
	}

	void Buffer::SetData(uchar* thePtr, int theCount)
	{
		reinterpret_cast<void(__thiscall*)(Buffer*, uchar*, int)>(0x0050d3a0)(this, thePtr, theCount);
	}

	uchar Buffer::ReadByte() const
	{
		return reinterpret_cast<uchar(__thiscall*)(const Buffer*)>(0x004fce60)(this);
	}

	int Buffer::ReadNumBits(int theBits, bool isSigned) const
	{
		return reinterpret_cast<int(__thiscall*)(const Buffer*, int, bool)>(0x004fcf50)(this, theBits, isSigned);
	}

	bool Buffer::ReadBoolean() const
	{
		return reinterpret_cast<bool(__thiscall*)(const Buffer*)>(0x004fd030)(this);
	}

	short Buffer::ReadShort() const
	{
		return reinterpret_cast<short(__thiscall*)(const Buffer*)>(0x004fd040)(this);
	}

	long Buffer::ReadLong() const
	{
		return reinterpret_cast<long(__thiscall*)(const Buffer*)>(0x004fd070)(this);
	}

	std::string Buffer::ReadString() const
	{
		return reinterpret_cast<std::string(__thiscall*)(const Buffer*)>(0x00503680)(this);
	}

	std::string Buffer::ReadLine() const
	{
		return reinterpret_cast<std::string(__thiscall*)(const Buffer*)>(0x00503720)(this);
	}

	void Buffer::ReadBytes(uchar* theData, int theLen) const
	{
		reinterpret_cast<void(__thiscall*)(const Buffer*, uchar*, int)>(0x004fd0b0)(this, theData, theLen);
	}

	const uchar* Buffer::GetDataPtr() const
	{
		return reinterpret_cast<const uchar*(__thiscall*)(const Buffer*)>(0x004fd0e0)(this);
	}

	int Buffer::GetDataLen() const
	{
		return reinterpret_cast<int(__thiscall*)(const Buffer*)>(0x004fbd30)(this);
	}

	bool Buffer::AtEnd() const
	{
		return reinterpret_cast<bool(__thiscall*)(const Buffer*)>(0x004fbd40)(this);
	}
}