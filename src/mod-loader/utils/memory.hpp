#pragma once

#include <functional>

template <typename T> inline std::function<T> call(std::uintptr_t callback)
{
	return std::function<T>(reinterpret_cast<T*>(callback));
}
