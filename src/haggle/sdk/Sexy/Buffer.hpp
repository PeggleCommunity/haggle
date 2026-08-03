#pragma once

#include "../../utils/defs.h"

#include <string>

namespace Sexy
{
	class __declspec(dllexport) Buffer
	{
	public:
		Buffer();
		~Buffer();

		std::string ToWebString() const;
		std::wstring UTF8ToWideString() const;

		void SeekFront() const;
		void Clear();

		void WriteByte(uchar theByte);
		void WriteNumBits(int theNum, int theBits);
		void WriteBoolean(bool theBool);
		void WriteShort(short theShort);
		void WriteLong(long theLong);
		void WriteString(const std::string& theString);
		void WriteLine(const std::string& theString);
		void WriteBytes(const uchar* theByte, int theCount);

		void SetData(uchar* thePtr, int theCount);

		uchar ReadByte() const;
		int ReadNumBits(int theBits, bool isSigned) const;
		bool ReadBoolean() const;
		short ReadShort() const;
		long ReadLong() const;
		std::string ReadString() const;
		std::string ReadLine() const;
		void ReadBytes(uchar* theData, int theLen) const;

		const uchar* GetDataPtr() const;
		int GetDataLen() const;
		bool AtEnd() const;

	private:
		char bufferData[40]; // to get the compiler to cooperate
	};
}