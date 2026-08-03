#pragma once
#include <iostream>
#include <windows.h>

#include "core/DungeonManager.h"
#include "core/BattleManager.h"
#include "core/UIManager.h"
//#include "item/Inventory.h"
//#include "item/Item.h"
#include "character/Player.h"


class GameManager
{
private:
	BattleManager bm;
	DungeonManager dm;
	UI um;
	Player* player = nullptr;
	//Crafting cm;
	//���� ���¸� ����. �߰� ����(status?,crafting?,quiz?)
	//Player* player = nullptr;//�ӽ�
	//DungeonManager dm;

	enum class GameState {
		MainMenu,
		Dungeon,
		Battle,
		Inventory,
		Crafting,
		Status,
		Exit
	};
	GameState currentState;

	//void HandleMainMenu();	//���� �޴� ���
	void HandleDungeon();	//���� ���� ����
	void HandleCrafting();	//���ۼ�
	void HandleStatus();	//���� ���� �޴�
	void CreateCharacter();

public:
	GameManager() : currentState(GameState::MainMenu) {}

	void Run();	//���� ���� ����
};
