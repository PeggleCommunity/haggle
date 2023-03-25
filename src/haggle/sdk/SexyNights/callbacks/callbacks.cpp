#include "callbacks.hpp"
#include "utils/memory.hpp"

namespace SexyNights
{
	std::mutex callbacks::mtx_;
	std::vector<callback_<void __cdecl()>> callbacks::once_callbacks_;
	std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl()>>> callbacks::basic_callbacks_;
	std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(SexyNights::Ball*, SexyNights::PhysObj*, bool)>>> callbacks::peg_hit_callbacks_;
	std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(SexyNights::LogicMgr*, bool)>>> callbacks::begin_shot_callbacks_;
	std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(SexyNights::LogicMgr*)>>> callbacks::begin_turn_2_callbacks_;
	std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(SexyNights::MainMenu*)>>> callbacks::main_menu_update_callbacks_;
	std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(SexyNights::Board*, std::string&)>>> callbacks::load_level_callbacks_;
	std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(SexyNights::LevelScreen*, unsigned int)>>> callbacks::do_play_callbacks_;
	std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(SexyNights::MainMenu*)>>> callbacks::start_game_callbacks_;

	//Sexy::SexyAppBase::DoMainLoop
	void __declspec(naked) main_loop()
	{
		static constexpr auto hook_type = callbacks::type::main_loop;
		__asm
		{
			push esi;
			mov esi, ecx;
			cmp byte ptr[esi + 341h], 0;
			jnz short loc_54CC05;
			lea esp, [esp + 0];

		loc_54CBE0:
			cmp byte ptr[esi + 342h], 0;
			jz short loc_54CBF0;
			mov byte ptr[esi + 342h], 0;

		loc_54CBF0:
			mov eax, [esi];
			mov edx, [eax + 188h];
			mov ecx, esi;

			pushad;
			push hook_type;
			call callbacks::run_basic_callbacks;
			add esp, 0x04;
			popad;

			call edx;
			cmp byte ptr[esi + 341h], 0;
			jz short loc_54CBE0;

		loc_54CC05:
			pop esi;
			retn;
		}
	}

	void callbacks::init()
	{
		jump(0x0054CBD0, main_loop);

		callbacks::on(type::main_loop, []() -> void
		{
			const std::lock_guard<std::mutex> lock(callbacks::mtx_);

			for (const auto callback : callbacks::once_callbacks_)
			{
				callback();
			}

			callbacks::once_callbacks_.clear();
		});
	}

	void callbacks::on(callbacks::type type, callback_<void __cdecl()> callback)
	{
		callbacks::basic_callbacks_[type].emplace_back(callback);
	}

	void callbacks::on(const std::initializer_list<callbacks::type>& types, callback_<void __cdecl()> callback)
	{
		for (const auto type : types)
		{
			callbacks::basic_callbacks_[type].emplace_back(callback);
		}
	}

	void callbacks::on_peg_hit(callback_<void __cdecl(SexyNights::Ball*, SexyNights::PhysObj*, bool)> callback)
	{
		callbacks::peg_hit_callbacks_[callbacks::type::peg_hit].emplace_back(callback);
	}

	void callbacks::after_peg_hit(callback_<void __cdecl(SexyNights::Ball*, SexyNights::PhysObj*, bool)> callback)
	{
		callbacks::peg_hit_callbacks_[callbacks::type::after_peg_hit].emplace_back(callback);
	}

	void callbacks::on_begin_shot(callback_<void __cdecl(SexyNights::LogicMgr*, bool)> callback)
	{
		callbacks::begin_shot_callbacks_[callbacks::type::begin_shot].emplace_back(callback);
	}

	void callbacks::after_begin_shot(callback_<void __cdecl(SexyNights::LogicMgr*, bool)> callback)
	{
		callbacks::begin_shot_callbacks_[callbacks::type::after_begin_shot].emplace_back(callback);
	}

	void callbacks::after_begin_turn_2(callback_<void __cdecl(SexyNights::LogicMgr*)> callback)
	{
		callbacks::begin_turn_2_callbacks_[callbacks::type::after_begin_turn_2].emplace_back(callback);
	}

	void callbacks::after_main_menu_update(callback_<void __cdecl(SexyNights::MainMenu*)> callback)
	{
		callbacks::main_menu_update_callbacks_[callbacks::type::after_main_menu_update].emplace_back(callback);
	}

	void callbacks::on_load_level(callback_<void __cdecl(SexyNights::Board*, std::string&)> callback)
	{
		callbacks::load_level_callbacks_[callbacks::type::load_level].emplace_back(callback);
	}

	void callbacks::on_do_play(callback_<void __cdecl(SexyNights::LevelScreen*, unsigned int)> callback)
	{
		callbacks::do_play_callbacks_[callbacks::type::do_play].emplace_back(callback);
	}

	void callbacks::after_do_play(callback_<void __cdecl(SexyNights::LevelScreen*, unsigned int)> callback)
	{
		callbacks::do_play_callbacks_[callbacks::type::after_do_play].emplace_back(callback);
	}

	void callbacks::after_start_game(callback_<void __cdecl(SexyNights::MainMenu*)> callback)
	{
		callbacks::start_game_callbacks_[callbacks::type::after_start_game].emplace_back(callback);
	}

	void callbacks::once(callback_<void __cdecl()> callback)
	{
		const std::lock_guard<std::mutex> lock(callbacks::mtx_);

		callbacks::once_callbacks_.emplace_back(callback);
	}

	void callbacks::run_basic_callbacks(callbacks::type type)
	{
		for (const auto callback : callbacks::basic_callbacks_[type])
		{
			callback();
		}
	}

	void callbacks::run_peg_hit_callbacks(SexyNights::Ball* ball, SexyNights::PhysObj* phys_obj, bool a4)
	{
		for (const auto peg_hit_callback : callbacks::peg_hit_callbacks_[callbacks::type::peg_hit])
		{
			peg_hit_callback(ball, phys_obj, a4);
		}
	}

	void callbacks::run_after_peg_hit_callbacks(SexyNights::Ball* ball, SexyNights::PhysObj* phys_obj, bool a4)
	{
		for (const auto peg_hit_callback : callbacks::peg_hit_callbacks_[callbacks::type::after_peg_hit])
		{
			peg_hit_callback(ball, phys_obj, a4);
		}
	}

	void callbacks::run_begin_shot_callbacks(SexyNights::LogicMgr* logic_mgr, bool doGetReplayPoint)
	{
		for (const auto begin_shot_callback : callbacks::begin_shot_callbacks_[callbacks::type::begin_shot])
		{
			begin_shot_callback(logic_mgr, doGetReplayPoint);
		}
	}

	void callbacks::run_after_begin_shot_callbacks(SexyNights::LogicMgr* logic_mgr, bool doGetReplayPoint)
	{
		for (const auto begin_shot_callback : callbacks::begin_shot_callbacks_[callbacks::type::after_begin_shot])
		{
			begin_shot_callback(logic_mgr, doGetReplayPoint);
		}
	}

	void callbacks::run_after_begin_turn_2_callbacks(SexyNights::LogicMgr* logic_mgr)
	{
		for (const auto begin_turn_2_callback : callbacks::begin_turn_2_callbacks_[callbacks::type::after_begin_turn_2])
		{
			begin_turn_2_callback(logic_mgr);
		}
	}

	void callbacks::run_after_main_menu_update_callbacks(SexyNights::MainMenu* main_menu)
	{
		for (const auto main_menu_update : callbacks::main_menu_update_callbacks_[callbacks::type::after_main_menu_update])
		{
			main_menu_update(main_menu);
		}
	}

	void callbacks::run_load_level_callbacks(SexyNights::Board* board, std::string& level_name)
	{
		for (const auto load_level : callbacks::load_level_callbacks_[callbacks::type::load_level])
		{
			load_level(board, level_name);
		}
	}

	void callbacks::run_do_play_callbacks(SexyNights::LevelScreen* level_screen, unsigned int a3)
	{
		for (const auto doplay : callbacks::do_play_callbacks_[callbacks::type::do_play])
		{
			doplay(level_screen, a3);
		}
	}

	void callbacks::run_after_do_play_callbacks(SexyNights::LevelScreen* level_screen, unsigned int a3)
	{
		for (const auto doplay : callbacks::do_play_callbacks_[callbacks::type::after_do_play])
		{
			doplay(level_screen, a3);
		}
	}

	void callbacks::run_after_start_game_callbacks(SexyNights::MainMenu* main_menu)
	{
		for (const auto after_start_game : callbacks::start_game_callbacks_[callbacks::type::after_start_game])
		{
			after_start_game(main_menu);
		}
	}
}
