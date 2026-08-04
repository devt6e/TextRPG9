#pragma once
#include <iostream>
#include <windows.h>

#include "core/DungeonManager.h"
#include "core/BattleManager.h"
#include "core/UIManager.h"
#include "item/Inventory.h"
#include "item/Item.h"
#include "item/Shop.h"
#include "character/Player.h"
#include "character/P_Warrior.h"
#include "character/P_Magician.h"
#include "character/P_Thief.h"

class GameManager
{

public:
	GameManager() : currentState(GameState::MainMenu) {}
	enum class GameState {
		MainMenu,
		Dungeon,
		Inventory,
		Store,
		Exit
	};

	void SetCurrentState(GameState gs) { this->currentState = gs; }
	GameState GetCurrentState() { return currentState; }
	void Run();	//���� ���� ����

private:
	BattleManager bm;
	DungeonManager dm;
	InventoryManager im;
	ShopManager sm;
	UI um;
	Player* player = nullptr;
	
	//Player* player = nullptr;//�ӽ�
	//DungeonManager dm;

	GameState currentState;

	//void HandleMainMenu();	//
	void HandleDungeon();	//던전입장루틴
	void HandleStore();		//상점이용루틴
	void HandleInventory();	//인벤토리루틴

	//void CreateCharacter(); //legacy: 멤버에서 분리했음

	
};
