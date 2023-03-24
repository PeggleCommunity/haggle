#pragma once

#include <mutex>
#include <vector>
#include <unordered_map>
#include "sdk/SexyNightsSDK.hpp"

template <typename F> using callback_ = F*;

namespace SexyNights
{
	class __declspec(dllexport) callbacks final
	{
	public:
		enum class type : std::uint32_t
		{
			main_loop,
		};

		static void init();

		static void on(callbacks::type type, callback_<void __cdecl()> callback);
		static void on(const std::initializer_list<callbacks::type>& types, callback_<void __cdecl()> callback);

		static void once(callback_<void __cdecl()> callback);

		static void run_basic_callbacks(callbacks::type type);
	private:

		static std::mutex mtx_;
		static std::vector<callback_<void __cdecl()>> once_callbacks_;

		static std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl()>>> basic_callbacks_;
	};
}
