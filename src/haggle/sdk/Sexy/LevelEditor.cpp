#include "LevelEditor.hpp"

Sexy::LevelEditor* Sexy::LevelEditor::levelEditor;

static Sexy::LevelEditor* (__fastcall* Sexy__LevelEditor__LevelEditor_)(Sexy::LevelEditor*, char*, Sexy::Board*);
Sexy::LevelEditor* __fastcall Sexy__LevelEditor__LevelEditor(Sexy::LevelEditor* this_, char* edx, Sexy::Board* theBoard)
{
	Sexy::LevelEditor::levelEditor = this_;
	return Sexy__LevelEditor__LevelEditor_(this_, edx, theBoard);
}

void Sexy::LevelEditor::setup()
{
	MH_CreateHook((void*)0x00422ab0, Sexy__LevelEditor__LevelEditor, (void**)&Sexy__LevelEditor__LevelEditor_);
}

bool Sexy::LevelEditor::check_exists()
{
	if (Sexy::LevelEditor::levelEditor == 0x0) return false;
	return true;
}

void Sexy::LevelEditor::ShowLevelEditor(char p1, char p2)
{
	if (!Sexy::LevelEditor::check_exists()) return;
	reinterpret_cast<void(__thiscall*)(Sexy::LevelEditor*, char, char)>(0x0042e620)(Sexy::LevelEditor::levelEditor, p1, p2);
}