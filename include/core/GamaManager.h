#pragma once
#include <iostream>
#include <windows.h>

#include "core/DungeonManager.h"
#include "core/BattleManager.h"
#include "core/UIManager.h"
#include "item/Inventory.h"
#include "item/Item.h"
#include "character/Player.h"
#include "character/P_Warrior.h"
#include "character/P_Archer.h"
#include "character/P_Magician.h"
#include "character/P_Thief.h"

class GameManager
{

public:
	GameManager() : currentState(GameState::MainMenu) {}
	enum class GameState {
		MainMenu,
		Dungeon,
		Battle,
		Inventory,
		Crafting,
		Status,
		Exit
	};

	void SetCurrentState(GameState gs) { this->currentState = gs; }
	GameState GetCurrentState() { return currentState; }
	void Run();	// 메인 게임 루프

private:
	BattleManager bm;
	DungeonManager dm;
	UI um;
	Player* player = nullptr;
	InventoryManager im;
	//Crafting cm;
	// 게임 상태 관리
	//Player* player = nullptr;// 임시
	//DungeonManager dm;

	GameState currentState;

	//void HandleMainMenu();	// 메인 메뉴 출력
	void HandleDungeon();	// 던전 처리
	void HandleCrafting();	// 제작소
	void HandleStatus();	// 스탯 관리 메뉴
	void HandleInventory();

	//void CreateCharacter(); //legacy: 멤버에서 분리했음

	
};
