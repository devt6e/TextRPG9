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
	void Run();	//���� ���� ����

private:
	BattleManager bm;
	DungeonManager dm;
	UI um;
	Player* player = nullptr;
	InventoryManager im;
	//Crafting cm;
	//���� ���¸� ����. �߰� ����(status?,crafting?,quiz?)
	//Player* player = nullptr;//�ӽ�
	//DungeonManager dm;

	GameState currentState;

	//void HandleMainMenu();	//���� �޴� ���
	void HandleDungeon();	//���� ���� ����
	void HandleCrafting();	//���ۼ�
	void HandleStatus();	//���� ���� �޴�
	void HandleInventory();

	//void CreateCharacter(); //legacy: 멤버에서 분리했음

	
};
