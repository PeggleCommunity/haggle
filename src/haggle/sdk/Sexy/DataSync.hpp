#pragma once

#include "../../utils/defs.h"

#include <string>

namespace Sexy
{
	class RefCount;

	class __declspec(dllexport) DataReader
	{
	public:
		DataReader();
		~DataReader();

		void OpenMemory(const void* theMemory, ulong theLength, bool deallocate);
		bool OpenFile(const std::string& theFileName);
		void Close();
		void ReadBytes(void* theBuffer, ulong theLength);
		ulong ReadLong();
		ushort ReadShort();
		uchar ReadByte();
		bool ReadBool();
		float ReadFloat();
		void ReadString(std::string& theString);
		bool ReadBit();
		void EndBit();

	private:
		char mStorage[0x80];
	};

	class __declspec(dllexport) DataWriter
	{
	public:
		DataWriter();
		~DataWriter();

		void OpenMemory(ulong theLength);
		void Close();
		void EnsureCapacity(ulong theLength);
		void WriteBytes(const void* theBuffer, ulong theLength);
		void WriteLong(ulong theValue);
		void WriteShort(ushort theValue);
		void WriteByte(uchar theValue);
		void WriteBool(bool theValue);
		void WriteFloat(float theValue);
		void WriteString(const std::string& theString);
		void WriteBit(bool theValue);
		void EndBit();
		void SetLong(ulong param_1, ulong param_2);

	private:
		char mStorage[0x80];
	};

	class __declspec(dllexport) DataSync
	{
	public:
		DataSync();
		explicit DataSync(DataReader& reader);
		explicit DataSync(DataWriter& writer);
		~DataSync();

		void SyncBytes(void* theValue, ulong theSize);
		void SyncLong(int& theValue);
		void SyncLong(unsigned long& theValue);
		void SyncShort(unsigned short& theValue);
		void SyncSShort(int& theValue);
		void SyncByte(int& theValue);
		void SyncSByte(int& theValue);
		void SyncBool(bool& theValue);
		void SyncFloat(float& theValue);
		void SyncString(std::string& theValue);
		void SyncBoolBit(bool& theValue);
		void EndBit();
		void SyncPointers();
		int AddRefCount(RefCount* refCount);
		RefCount* GetRefCount(int theIndex);
		void Reset();
		void ResetPointerTable();
		DataReader* StartReadMemory(const void* theMemory, ulong theLength, bool deallocate);
		void SetReader(DataReader* theReader);
		DataWriter* StartWriteMemory(ulong theLength);
		void SetWriter(DataWriter* theWriter);

	private:
		char mStorage[0x200];
	};
}