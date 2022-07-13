#pragma once

#include <mutex>
#include <vector>
#include <unordered_map>
#include "sdk/SexySDK.hpp"

template <typename F> using callback_ = F*;

class callbacks final
{
public:
	enum class type : std::uint32_t
	{
		main_loop,
		peg_hit,
		beginturn2,
		begin_shot,
	};
		
	static void init();

	static void on(callbacks::type type, callback_<void __cdecl()> callback);
	static void on(const std::initializer_list<callbacks::type>& types, callback_<void __cdecl()> callback);

	static void on_peg_hit(callback_<void __cdecl(Sexy::Ball*, Sexy::PhysObj*, bool)> callback);
	static void on_begin_shot(callback_<void __cdecl(Sexy::LogicMgr*, char)> callback);

	static void once(callback_<void __cdecl()> callback);

	static void run_basic_callbacks(callbacks::type type);
	static void run_peg_hit_callbacks(Sexy::Ball* ball, Sexy::PhysObj* phys_obj, bool a4);
	static void run_begin_shot_callbacks(Sexy::LogicMgr* logic_mgr, char a2);

private:

	static std::mutex mtx_;
	static std::vector<callback_<void __cdecl()>> once_callbacks_;
		
	static std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl()>>> basic_callbacks_;
	static std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(Sexy::Ball*, Sexy::PhysObj*, bool)>>> peg_hit_callbacks_;
	static std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(Sexy::LogicMgr*, char)>>> begin_shot_callbacks_;
};
