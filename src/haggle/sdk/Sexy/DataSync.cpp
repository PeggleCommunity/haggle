#include "DataSync.hpp"

namespace Sexy
{
	DataReader::DataReader()
	{
		reinterpret_cast<void(__thiscall*)(DataReader*)>(0x004bbe20)(this);
	}

	DataReader::~DataReader()
	{
		reinterpret_cast<void(__thiscall*)(DataReader*)>(0x004bbec0)(this);
	}

	void DataReader::OpenMemory(const void* theMemory, ulong theLength, bool deallocate)
	{
		reinterpret_cast<void(__thiscall*)(DataReader*, const void*, ulong, bool)>(0x004bbed0)(this, theMemory, theLength, deallocate);
	}

	bool DataReader::OpenFile(const std::string& theFileName)
	{
		return reinterpret_cast<bool(__thiscall*)(DataReader*, const std::string&)>(0x004bbf30)(this, theFileName);
	}

	void DataReader::Close()
	{
		reinterpret_cast<void(__thiscall*)(DataReader*)>(0x004bbe60)(this);
	}

	void DataReader::ReadBytes(void* theBuffer, ulong theLength)
	{
		reinterpret_cast<void(__thiscall*)(DataReader*, void*, ulong)>(0x004bbf70)(this, theBuffer, theLength);
	}

	ulong DataReader::ReadLong()
	{
		return reinterpret_cast<ulong(__thiscall*)(DataReader*)>(0x004bc190)(this);
	}

	ushort DataReader::ReadShort()
	{
		return reinterpret_cast<ushort(__thiscall*)(DataReader*)>(0x004bc1b0)(this);
	}

	uchar DataReader::ReadByte()
	{
		return reinterpret_cast<uchar(__thiscall*)(DataReader*)>(0x004bc1d0)(this);
	}

	bool DataReader::ReadBool()
	{
		return reinterpret_cast<bool(__thiscall*)(DataReader*)>(0x004bc1f0)(this);
	}

	float DataReader::ReadFloat()
	{
		return reinterpret_cast<float(__thiscall*)(DataReader*)>(0x004bc200)(this);
	}

	void DataReader::ReadString(std::string& theString)
	{
		reinterpret_cast<void(__thiscall*)(DataReader*, std::string&)>(0x004bc220)(this, theString);
	}

	bool DataReader::ReadBit()
	{
		return reinterpret_cast<bool(__thiscall*)(DataReader*)>(0x004bc290)(this);
	}

	void DataReader::EndBit()
	{
		reinterpret_cast<void(__thiscall*)(DataReader*)>(0x004bbeb0)(this);
	}

	DataWriter::DataWriter()
	{
		reinterpret_cast<void(__thiscall*)(DataWriter*)>(0x004bba70)(this);
	}

	DataWriter::~DataWriter()
	{
		reinterpret_cast<void(__thiscall*)(DataWriter*)>(0x004bbd20)(this);
	}

	void DataWriter::OpenMemory(ulong theLength)
	{
		reinterpret_cast<void(__thiscall*)(DataWriter*, ulong)>(0x004bbd70)(this, theLength);
	}

	void DataWriter::Close()
	{
		reinterpret_cast<void(__thiscall*)(DataWriter*)>(0x004bbc40)(this);
	}

	void DataWriter::EnsureCapacity(ulong theLength)
	{
		reinterpret_cast<void(__thiscall*)(DataWriter*, ulong)>(0x004bbac0)(this, theLength);
	}

	void DataWriter::WriteBytes(const void* theBuffer, ulong theLength)
	{
		reinterpret_cast<void(__thiscall*)(DataWriter*, const void*, ulong)>(0x004bbb10)(this, theBuffer, theLength);
	}

	void DataWriter::WriteLong(ulong theValue)
	{
		reinterpret_cast<void(__thiscall*)(DataWriter*, ulong)>(0x004bbb90)(this, theValue);
	}

	void DataWriter::WriteShort(ushort theValue)
	{
		reinterpret_cast<void(__thiscall*)(DataWriter*, ushort)>(0x004bbbb0)(this, theValue);
	}

	void DataWriter::WriteByte(uchar theValue)
	{
		reinterpret_cast<void(__thiscall*)(DataWriter*, uchar)>(0x004bbbd0)(this, theValue);
	}

	void DataWriter::WriteBool(bool theValue)
	{
		reinterpret_cast<void(__thiscall*)(DataWriter*, bool)>(0x004bbbf0)(this, theValue);
	}

	void DataWriter::WriteFloat(float theValue)
	{
		reinterpret_cast<void(__thiscall*)(DataWriter*, float)>(0x004bbb90)(this, theValue);
	}

	void DataWriter::WriteString(const std::string& theString)
	{
		reinterpret_cast<void(__thiscall*)(DataWriter*, const std::string&)>(0x004bbda0)(this, theString);
	}

	void DataWriter::WriteBit(bool theValue)
	{
		reinterpret_cast<void(__thiscall*)(DataWriter*, bool)>(0x004bbc90)(this, theValue);
	}

	void DataWriter::EndBit()
	{
		reinterpret_cast<void(__thiscall*)(DataWriter*)>(0x004bba90)(this);
	}

	void DataWriter::SetLong(ulong param_1, ulong param_2)
	{
		reinterpret_cast<void(__thiscall*)(DataWriter*, ulong, ulong)>(0x004bbc10)(this, param_1, param_2);
	}

	DataSync::DataSync()
	{
		reinterpret_cast<void(__thiscall*)(DataSync*)>(0x004bb6f0)(this);
	}

	DataSync::DataSync(DataReader& reader)
	{
		reinterpret_cast<void(__thiscall*)(DataSync*, DataReader&)>(0x004bb810)(this, reader);
	}

	DataSync::DataSync(DataWriter& writer)
	{
		reinterpret_cast<void(__thiscall*)(DataSync*, DataWriter&)>(0x004bb940)(this, writer);
	}

	DataSync::~DataSync()
	{
		reinterpret_cast<void(__thiscall*)(DataSync*)>(0x004bb0b0)(this);
	}

	void DataSync::SyncBytes(void* theValue, ulong theSize)
	{
		reinterpret_cast<void(__thiscall*)(DataSync*, void*, ulong)>(0x004ba7f0)(this, theValue, theSize);
	}

	void DataSync::SyncLong(int& theValue)
	{
		reinterpret_cast<void(__thiscall*)(DataSync*, int&)>(0x004ba810)(this, theValue);
	}

	void DataSync::SyncLong(unsigned long& theValue)
	{
		reinterpret_cast<void(__thiscall*)(DataSync*, unsigned long&)>(0x004ba810)(this, theValue);
	}

	void DataSync::SyncShort(unsigned short& theValue)
	{
		reinterpret_cast<void(__thiscall*)(DataSync*, unsigned short&)>(0x004ba840)(this, theValue);
	}

	void DataSync::SyncSShort(int& theValue)
	{
		reinterpret_cast<void(__thiscall*)(DataSync*, int&)>(0x004ba870)(this, theValue);
	}

	void DataSync::SyncByte(int& theValue)
	{
		reinterpret_cast<void(__thiscall*)(DataSync*, int&)>(0x004ba8a0)(this, theValue);
	}

	void DataSync::SyncSByte(int& theValue)
	{
		reinterpret_cast<void(__thiscall*)(DataSync*, int&)>(0x004ba8d0)(this, theValue);
	}

	void DataSync::SyncBool(bool& theValue)
	{
		reinterpret_cast<void(__thiscall*)(DataSync*, bool&)>(0x004ba920)(this, theValue);
	}

	void DataSync::SyncFloat(float& theValue)
	{
		reinterpret_cast<void(__thiscall*)(DataSync*, float&)>(0x004ba980)(this, theValue);
	}

	void DataSync::SyncString(std::string& theValue)
	{
		reinterpret_cast<void(__thiscall*)(DataSync*, std::string&)>(0x004ba9b0)(this, theValue);
	}

	void DataSync::SyncBoolBit(bool& theValue)
	{
		reinterpret_cast<void(__thiscall*)(DataSync*, bool&)>(0x004ba950)(this, theValue);
	}

	void DataSync::EndBit()
	{
		reinterpret_cast<void(__thiscall*)(DataSync*)>(0x004ba900)(this);
	}

	void DataSync::SyncPointers()
	{
		reinterpret_cast<void(__thiscall*)(DataSync*)>(0x004bb3e0)(this);
	}

	int DataSync::AddRefCount(RefCount* refCount)
	{
		return reinterpret_cast<int(__thiscall*)(DataSync*, RefCount*)>(0x004bb330)(this, refCount);
	}

	RefCount* DataSync::GetRefCount(int theIndex)
	{
		return reinterpret_cast<RefCount*(__thiscall*)(DataSync*, int)>(0x004baac0)(this, theIndex);
	}

	void DataSync::Reset()
	{
		reinterpret_cast<void(__thiscall*)(DataSync*)>(0x004bb630)(this);
	}

	void DataSync::ResetPointerTable()
	{
		reinterpret_cast<void(__thiscall*)(DataSync*)>(0x004bb1f0)(this);
	}

	DataReader* DataSync::StartReadMemory(const void* theMemory, ulong theLength, bool deallocate)
	{
		return reinterpret_cast<DataReader*(__thiscall*)(DataSync*, const void*, ulong, bool)>(0x004bb6a0)(this, theMemory, theLength, deallocate);
	}

	void DataSync::SetReader(DataReader* theReader)
	{
		reinterpret_cast<void(__thiscall*)(DataSync*, DataReader*)>(0x004bb660)(this, theReader);
	}

	DataWriter* DataSync::StartWriteMemory(ulong theLength)
	{
		return reinterpret_cast<DataWriter*(__thiscall*)(DataSync*, ulong)>(0x004bb6d0)(this, theLength);
	}

	void DataSync::SetWriter(DataWriter* theWriter)
	{
		reinterpret_cast<void(__thiscall*)(DataSync*, DataWriter*)>(0x004bb680)(this, theWriter);
	}
}