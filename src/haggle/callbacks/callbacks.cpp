#include "callbacks.hpp"
#include "memory.hpp"

std::mutex callbacks::mtx_;
std::vector<callback_<void __cdecl()>> callbacks::once_callbacks_;
std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl()>>> callbacks::basic_callbacks_;
std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(Sexy::Ball*, Sexy::PhysObj*, bool)>>> callbacks::peg_hit_callbacks_;
std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(Sexy::LogicMgr*, char)>>> callbacks::begin_shot_callbacks_;

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

void callbacks::run_begin_shot_callbacks(Sexy::LogicMgr* logic_mgr, char a2)
{
	for (const auto begin_shot_callback : callbacks::begin_shot_callbacks_[callbacks::type::begin_shot])
	{
		begin_shot_callback(logic_mgr, a2);
	}
}
