#pragma once

template <typename T> static void jump(std::uint32_t address, T function)
{
	//Un-protection of memory segment being accessed
	DWORD protecc;
	VirtualProtect(reinterpret_cast<void*>(address), 5, PAGE_EXECUTE_READWRITE, &protecc);

	//Place our jump...
	*(std::uint8_t*)(address) = 0xE9;
	//...to our function
	*(std::uint32_t*)(address + 1) = (std::uint32_t(function) - address - 5);

	//Re-protect it as we are done
	VirtualProtect(reinterpret_cast<void*>(address), 5, protecc, &protecc);
};
