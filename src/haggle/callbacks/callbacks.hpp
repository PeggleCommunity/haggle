#pragma once

#include <mutex>
#include <vector>
#include <unordered_map>
#include "sdk/SexySDK.hpp"

template <typename F> using callback_ = F*;

class __declspec(dllexport) callbacks final
{
public:
	enum class type : std::uint32_t
	{
		main_loop,
		peg_hit,
		after_peg_hit,
		begin_turn_2,
		after_begin_turn_2,
		begin_shot,
		after_begin_shot,
		show_adventure_screen,
		after_show_adventure_screen,
		start_adventure_game,
		after_start_adventure_game,
		just_beat_adventure_true,
		just_beat_adventure_false,
		do_to_menu,
		do_options_dialog,
		finish_options_dialog,
		finish_init_level,
		do_level_done,
		after_beat_level_true,
		after_beat_level_false,
		after_show_level_screen,
		after_main_menu_update,
	};
		
	static void init();

	static void on(callbacks::type type, callback_<void __cdecl()> callback);
	static void on(const std::initializer_list<callbacks::type>& types, callback_<void __cdecl()> callback);

	static void on_peg_hit(callback_<void __cdecl(Sexy::Ball*, Sexy::PhysObj*, bool)> callback);
	static void after_peg_hit(callback_<void __cdecl(Sexy::Ball*, Sexy::PhysObj*, bool)> callback);
	static void on_begin_shot(callback_<void __cdecl(Sexy::LogicMgr*, bool)> callback);
	static void after_begin_shot(callback_<void __cdecl(Sexy::LogicMgr*, bool)> callback);
	static void after_begin_turn_2(callback_<void __cdecl(Sexy::LogicMgr*)> callback);
	static void after_main_menu_update(callback_<void __cdecl(Sexy::MainMenu*)> callback);

	static void once(callback_<void __cdecl()> callback);

	static void run_basic_callbacks(callbacks::type type);
	static void run_peg_hit_callbacks(Sexy::Ball* ball, Sexy::PhysObj* phys_obj, bool a4);
	static void run_after_peg_hit_callbacks(Sexy::Ball* ball, Sexy::PhysObj* phys_obj, bool a4);
	static void run_begin_shot_callbacks(Sexy::LogicMgr* logic_mgr, bool doGetReplayPoint);
	static void run_after_begin_shot_callbacks(Sexy::LogicMgr* logic_mgr, bool doGetReplayPoint);
	static void run_after_begin_turn_2_callbacks(Sexy::LogicMgr* logic_mgr);
	static void run_after_main_menu_update(Sexy::MainMenu* logic_mgr);

private:

	static std::mutex mtx_;
	static std::vector<callback_<void __cdecl()>> once_callbacks_;
		
	static std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl()>>> basic_callbacks_;
	static std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(Sexy::Ball*, Sexy::PhysObj*, bool)>>> peg_hit_callbacks_;
	static std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(Sexy::LogicMgr*, bool)>>> begin_shot_callbacks_;
	static std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(Sexy::LogicMgr*)>>> begin_turn_2_callbacks_;
	static std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(Sexy::MainMenu*)>>> main_menu_update_callbacks_;
};
