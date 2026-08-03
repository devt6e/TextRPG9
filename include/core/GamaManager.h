#pragma once
#include <iostream>
#include <windows.h>

#include "core/DungeonManager.h"
#include "core/BattleManager.h"
#include "core/UIManager.h"
#include "item/Inventory.h"
#include "item/Item.h"
#include "character/Player.h"


class GameManager
{
private:
	BattleManager bm;
	DungeonManager dm;
	UI um;
	Player* player = nullptr;
	//Crafting cm;
	//게임 상태를 관리. 추가 예정(status?,crafting?,quiz?)
	enum class GameState {
		MainMenu,
		Dungeon,
		Battle,
		Inventory,
		Crafting,
		Exit
	};
	GameState currentState;

	//void HandleMainMenu();	//메인 메뉴 출력
	void HandleDungeon();	//던전 입장 로직
	void HandleCrafting();	//제작소
	void HandleStatus();	//스탯 관리 메뉴
	void CreateCharacter();

public:
	GameManager() : currentState(GameState::MainMenu) {}

	void Run();	//메인 게임 루프
};
