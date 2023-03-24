#include "callbacks.hpp"
#include "utils/memory.hpp"

namespace Sexy
{
	std::mutex callbacks::mtx_;
	std::vector<callback_<void __cdecl()>> callbacks::once_callbacks_;
	std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl()>>> callbacks::basic_callbacks_;
	std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(Sexy::Ball*, Sexy::PhysObj*, bool)>>> callbacks::peg_hit_callbacks_;
	std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(Sexy::LogicMgr*, bool)>>> callbacks::begin_shot_callbacks_;
	std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(Sexy::LogicMgr*)>>> callbacks::begin_turn_2_callbacks_;
	std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(Sexy::MainMenu*)>>> callbacks::main_menu_update_callbacks_;
	std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(Sexy::Board*, std::string&)>>> callbacks::load_level_callbacks_;
	std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(Sexy::LevelScreen*, unsigned int)>>> callbacks::do_play_callbacks_;
	std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(Sexy::MainMenu*)>>> callbacks::start_game_callbacks_;

	//Sexy::SexyAppBase::DoMainLoop
	void __declspec(naked) main_loop()
	{
		static constexpr auto hook_type = callbacks::type::main_loop;

		__asm
		{
			push esi;
			mov esi, ecx;
			cmp byte ptr[esi + 341h], 0;
			jnz short loc_52A625;

		loc_52A600:
			cmp byte ptr[esi + 342h], 0;
			jz short loc_52A610;
			mov byte ptr[esi + 342h], 0;

		loc_52A610:
			mov eax, [esi];
			mov edx, [eax + 180h];
			mov ecx, esi;

			pushad;
			push hook_type;
			call callbacks::run_basic_callbacks;
			add esp, 0x04;
			popad;

			call edx;
			cmp byte ptr[esi + 341h], 0;
			jz short loc_52A600;

		loc_52A625:
			pop esi;
			retn;
		}
	}

	void callbacks::init()
	{
		jump(0x0052A5F0, main_loop);

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

	void callbacks::on_peg_hit(callback_<void __cdecl(Sexy::Ball*, Sexy::PhysObj*, bool)> callback)
	{
		callbacks::peg_hit_callbacks_[callbacks::type::peg_hit].emplace_back(callback);
	}

	void callbacks::after_peg_hit(callback_<void __cdecl(Sexy::Ball*, Sexy::PhysObj*, bool)> callback)
	{
		callbacks::peg_hit_callbacks_[callbacks::type::after_peg_hit].emplace_back(callback);
	}

	void callbacks::on_begin_shot(callback_<void __cdecl(Sexy::LogicMgr*, bool)> callback)
	{
		callbacks::begin_shot_callbacks_[callbacks::type::begin_shot].emplace_back(callback);
	}

	void callbacks::after_begin_shot(callback_<void __cdecl(Sexy::LogicMgr*, bool)> callback)
	{
		callbacks::begin_shot_callbacks_[callbacks::type::after_begin_shot].emplace_back(callback);
	}

	void callbacks::after_begin_turn_2(callback_<void __cdecl(Sexy::LogicMgr*)> callback)
	{
		callbacks::begin_turn_2_callbacks_[callbacks::type::after_begin_turn_2].emplace_back(callback);
	}

	void callbacks::after_main_menu_update(callback_<void __cdecl(Sexy::MainMenu*)> callback)
	{
		callbacks::main_menu_update_callbacks_[callbacks::type::after_main_menu_update].emplace_back(callback);
	}

	void callbacks::on_load_level(callback_<void __cdecl(Sexy::Board*, std::string&)> callback)
	{
		callbacks::load_level_callbacks_[callbacks::type::load_level].emplace_back(callback);
	}

	void callbacks::on_do_play(callback_<void __cdecl(Sexy::LevelScreen*, unsigned int)> callback)
	{
		callbacks::do_play_callbacks_[callbacks::type::do_play].emplace_back(callback);
	}

	void callbacks::after_do_play(callback_<void __cdecl(Sexy::LevelScreen*, unsigned int)> callback)
	{
		callbacks::do_play_callbacks_[callbacks::type::after_do_play].emplace_back(callback);
	}

	void callbacks::after_start_game(callback_<void __cdecl(Sexy::MainMenu*)> callback)
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

	void callbacks::run_peg_hit_callbacks(Sexy::Ball* ball, Sexy::PhysObj* phys_obj, bool a4)
	{
		for (const auto peg_hit_callback : callbacks::peg_hit_callbacks_[callbacks::type::peg_hit])
		{
			peg_hit_callback(ball, phys_obj, a4);
		}
	}

	void callbacks::run_after_peg_hit_callbacks(Sexy::Ball* ball, Sexy::PhysObj* phys_obj, bool a4)
	{
		for (const auto peg_hit_callback : callbacks::peg_hit_callbacks_[callbacks::type::after_peg_hit])
		{
			peg_hit_callback(ball, phys_obj, a4);
		}
	}

	void callbacks::run_begin_shot_callbacks(Sexy::LogicMgr* logic_mgr, bool doGetReplayPoint)
	{
		for (const auto begin_shot_callback : callbacks::begin_shot_callbacks_[callbacks::type::begin_shot])
		{
			begin_shot_callback(logic_mgr, doGetReplayPoint);
		}
	}

	void callbacks::run_after_begin_shot_callbacks(Sexy::LogicMgr* logic_mgr, bool doGetReplayPoint)
	{
		for (const auto begin_shot_callback : callbacks::begin_shot_callbacks_[callbacks::type::after_begin_shot])
		{
			begin_shot_callback(logic_mgr, doGetReplayPoint);
		}
	}

	void callbacks::run_after_begin_turn_2_callbacks(Sexy::LogicMgr* logic_mgr)
	{
		for (const auto begin_turn_2_callback : callbacks::begin_turn_2_callbacks_[callbacks::type::after_begin_turn_2])
		{
			begin_turn_2_callback(logic_mgr);
		}
	}

	void callbacks::run_after_main_menu_update_callbacks(Sexy::MainMenu* main_menu)
	{
		for (const auto main_menu_update : callbacks::main_menu_update_callbacks_[callbacks::type::after_main_menu_update])
		{
			main_menu_update(main_menu);
		}
	}

	void callbacks::run_load_level_callbacks(Sexy::Board* board, std::string& level_name)
	{
		for (const auto load_level : callbacks::load_level_callbacks_[callbacks::type::load_level])
		{
			load_level(board, level_name);
		}
	}

	void callbacks::run_do_play_callbacks(Sexy::LevelScreen* level_screen, unsigned int a3)
	{
		for (const auto doplay : callbacks::do_play_callbacks_[callbacks::type::do_play])
		{
			doplay(level_screen, a3);
		}
	}

	void callbacks::run_after_do_play_callbacks(Sexy::LevelScreen* level_screen, unsigned int a3)
	{
		for (const auto doplay : callbacks::do_play_callbacks_[callbacks::type::after_do_play])
		{
			doplay(level_screen, a3);
		}
	}

	void callbacks::run_after_start_game_callbacks(Sexy::MainMenu* main_menu)
	{
		for (const auto after_start_game : callbacks::start_game_callbacks_[callbacks::type::after_start_game])
		{
			after_start_game(main_menu);
		}
	}
}
